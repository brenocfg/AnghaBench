#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xcopy_op {int op_origin; int /*<<< orphan*/ * dst_tid_wwn; int /*<<< orphan*/  dst_dev; int /*<<< orphan*/ * src_tid_wwn; int /*<<< orphan*/  src_dev; int /*<<< orphan*/  dtdi; int /*<<< orphan*/  stdi; int /*<<< orphan*/ * local_dev_wwn; } ;
struct se_device {int dummy; } ;
struct se_cmd {struct se_device* se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned short RCR_OP_MAX_TARGET_DESC_COUNT ; 
 int /*<<< orphan*/  TCM_COPY_TARGET_DEVICE_NOT_REACHABLE ; 
 int /*<<< orphan*/  TCM_INVALID_PARAMETER_LIST ; 
 int /*<<< orphan*/  TCM_TOO_MANY_TARGET_DESCS ; 
 int /*<<< orphan*/  TCM_UNSUPPORTED_TARGET_DESC_TYPE_CODE ; 
#define  XCOL_DEST_RECV_OP 129 
#define  XCOL_SOURCE_RECV_OP 128 
 int /*<<< orphan*/  XCOPY_NAA_IEEE_REGEX_LEN ; 
 unsigned short XCOPY_TARGET_DESC_LEN ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned short,...) ; 
 int /*<<< orphan*/  target_xcopy_gen_naa_ieee (struct se_device*,int /*<<< orphan*/ *) ; 
 int target_xcopy_locate_se_dev_e4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int target_xcopy_parse_tiddesc_e4 (struct se_cmd*,struct xcopy_op*,unsigned char*,unsigned short) ; 

__attribute__((used)) static int target_xcopy_parse_target_descriptors(struct se_cmd *se_cmd,
				struct xcopy_op *xop, unsigned char *p,
				unsigned short tdll, sense_reason_t *sense_ret)
{
	struct se_device *local_dev = se_cmd->se_dev;
	unsigned char *desc = p;
	int offset = tdll % XCOPY_TARGET_DESC_LEN, rc;
	unsigned short cscd_index = 0;
	unsigned short start = 0;

	*sense_ret = TCM_INVALID_PARAMETER_LIST;

	if (offset != 0) {
		pr_err("XCOPY target descriptor list length is not"
			" multiple of %d\n", XCOPY_TARGET_DESC_LEN);
		*sense_ret = TCM_UNSUPPORTED_TARGET_DESC_TYPE_CODE;
		return -EINVAL;
	}
	if (tdll > RCR_OP_MAX_TARGET_DESC_COUNT * XCOPY_TARGET_DESC_LEN) {
		pr_err("XCOPY target descriptor supports a maximum"
			" two src/dest descriptors, tdll: %hu too large..\n", tdll);
		/* spc4r37 6.4.3.4 CSCD DESCRIPTOR LIST LENGTH field */
		*sense_ret = TCM_TOO_MANY_TARGET_DESCS;
		return -EINVAL;
	}
	/*
	 * Generate an IEEE Registered Extended designator based upon the
	 * se_device the XCOPY was received upon..
	 */
	memset(&xop->local_dev_wwn[0], 0, XCOPY_NAA_IEEE_REGEX_LEN);
	target_xcopy_gen_naa_ieee(local_dev, &xop->local_dev_wwn[0]);

	while (start < tdll) {
		/*
		 * Check target descriptor identification with 0xE4 type, and
		 * compare the current index with the CSCD descriptor IDs in
		 * the segment descriptor. Use VPD 0x83 WWPN matching ..
		 */
		switch (desc[0]) {
		case 0xe4:
			rc = target_xcopy_parse_tiddesc_e4(se_cmd, xop,
							&desc[0], cscd_index);
			if (rc != 0)
				goto out;
			start += XCOPY_TARGET_DESC_LEN;
			desc += XCOPY_TARGET_DESC_LEN;
			cscd_index++;
			break;
		default:
			pr_err("XCOPY unsupported descriptor type code:"
					" 0x%02x\n", desc[0]);
			*sense_ret = TCM_UNSUPPORTED_TARGET_DESC_TYPE_CODE;
			goto out;
		}
	}

	switch (xop->op_origin) {
	case XCOL_SOURCE_RECV_OP:
		rc = target_xcopy_locate_se_dev_e4(xop->dst_tid_wwn,
						&xop->dst_dev);
		break;
	case XCOL_DEST_RECV_OP:
		rc = target_xcopy_locate_se_dev_e4(xop->src_tid_wwn,
						&xop->src_dev);
		break;
	default:
		pr_err("XCOPY CSCD descriptor IDs not found in CSCD list - "
			"stdi: %hu dtdi: %hu\n", xop->stdi, xop->dtdi);
		rc = -EINVAL;
		break;
	}
	/*
	 * If a matching IEEE NAA 0x83 descriptor for the requested device
	 * is not located on this node, return COPY_ABORTED with ASQ/ASQC
	 * 0x0d/0x02 - COPY_TARGET_DEVICE_NOT_REACHABLE to request the
	 * initiator to fall back to normal copy method.
	 */
	if (rc < 0) {
		*sense_ret = TCM_COPY_TARGET_DEVICE_NOT_REACHABLE;
		goto out;
	}

	pr_debug("XCOPY TGT desc: Source dev: %p NAA IEEE WWN: 0x%16phN\n",
		 xop->src_dev, &xop->src_tid_wwn[0]);
	pr_debug("XCOPY TGT desc: Dest dev: %p NAA IEEE WWN: 0x%16phN\n",
		 xop->dst_dev, &xop->dst_tid_wwn[0]);

	return cscd_index;

out:
	return -EINVAL;
}