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
struct xcopy_op {int dummy; } ;
struct se_cmd {int dummy; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int RCR_OP_MAX_SG_DESC_COUNT ; 
 int /*<<< orphan*/  TCM_INVALID_PARAMETER_LIST ; 
 int /*<<< orphan*/  TCM_TOO_MANY_SEGMENT_DESCS ; 
 int /*<<< orphan*/  TCM_UNSUPPORTED_SEGMENT_DESC_TYPE_CODE ; 
 unsigned int XCOPY_SEGMENT_DESC_LEN ; 
 int /*<<< orphan*/  pr_err (char*,unsigned char,...) ; 
 int target_xcopy_parse_segdesc_02 (struct se_cmd*,struct xcopy_op*,unsigned char*) ; 

__attribute__((used)) static int target_xcopy_parse_segment_descriptors(struct se_cmd *se_cmd,
				struct xcopy_op *xop, unsigned char *p,
				unsigned int sdll, sense_reason_t *sense_ret)
{
	unsigned char *desc = p;
	unsigned int start = 0;
	int offset = sdll % XCOPY_SEGMENT_DESC_LEN, rc, ret = 0;

	*sense_ret = TCM_INVALID_PARAMETER_LIST;

	if (offset != 0) {
		pr_err("XCOPY segment descriptor list length is not"
			" multiple of %d\n", XCOPY_SEGMENT_DESC_LEN);
		*sense_ret = TCM_UNSUPPORTED_SEGMENT_DESC_TYPE_CODE;
		return -EINVAL;
	}
	if (sdll > RCR_OP_MAX_SG_DESC_COUNT * XCOPY_SEGMENT_DESC_LEN) {
		pr_err("XCOPY supports %u segment descriptor(s), sdll: %u too"
			" large..\n", RCR_OP_MAX_SG_DESC_COUNT, sdll);
		/* spc4r37 6.4.3.5 SEGMENT DESCRIPTOR LIST LENGTH field */
		*sense_ret = TCM_TOO_MANY_SEGMENT_DESCS;
		return -EINVAL;
	}

	while (start < sdll) {
		/*
		 * Check segment descriptor type code for block -> block
		 */
		switch (desc[0]) {
		case 0x02:
			rc = target_xcopy_parse_segdesc_02(se_cmd, xop, desc);
			if (rc < 0)
				goto out;

			ret++;
			start += XCOPY_SEGMENT_DESC_LEN;
			desc += XCOPY_SEGMENT_DESC_LEN;
			break;
		default:
			pr_err("XCOPY unsupported segment descriptor"
				"type: 0x%02x\n", desc[0]);
			*sense_ret = TCM_UNSUPPORTED_SEGMENT_DESC_TYPE_CODE;
			goto out;
		}
	}

	return ret;

out:
	return -EINVAL;
}