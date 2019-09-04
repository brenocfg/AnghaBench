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
struct lpfc_hba {int dummy; } ;
typedef  int /*<<< orphan*/  MAILBOX_t ;

/* Variables and functions */

void
lpfc_idiag_mbxacc_dump_issue_mbox(struct lpfc_hba *phba, MAILBOX_t *pmbox)
{
#ifdef CONFIG_SCSI_LPFC_DEBUG_FS
	uint32_t *mbx_dump_map, *mbx_dump_cnt, *mbx_word_cnt, *mbx_mbox_cmd;
	char line_buf[LPFC_MBX_ACC_LBUF_SZ];
	int len = 0;
	uint32_t *pword;
	uint8_t *pbyte;
	uint32_t i, j;

	if (idiag.cmd.opcode != LPFC_IDIAG_CMD_MBXACC_DP)
		return;

	mbx_mbox_cmd = &idiag.cmd.data[IDIAG_MBXACC_MBCMD_INDX];
	mbx_dump_map = &idiag.cmd.data[IDIAG_MBXACC_DPMAP_INDX];
	mbx_dump_cnt = &idiag.cmd.data[IDIAG_MBXACC_DPCNT_INDX];
	mbx_word_cnt = &idiag.cmd.data[IDIAG_MBXACC_WDCNT_INDX];

	if (!(*mbx_dump_map & LPFC_MBX_DMP_MBX_ALL) ||
	    (*mbx_dump_cnt == 0) ||
	    (*mbx_word_cnt == 0))
		return;

	if ((*mbx_mbox_cmd != LPFC_MBX_ALL_CMD) &&
	    (*mbx_mbox_cmd != pmbox->mbxCommand))
		return;

	/* dump buffer content */
	if (*mbx_dump_map & LPFC_MBX_DMP_MBX_WORD) {
		pr_err("Mailbox command:0x%x dump by word:\n",
		       pmbox->mbxCommand);
		pword = (uint32_t *)pmbox;
		for (i = 0; i < *mbx_word_cnt; i++) {
			if (!(i % 8)) {
				if (i != 0)
					pr_err("%s\n", line_buf);
				len = 0;
				memset(line_buf, 0, LPFC_MBX_ACC_LBUF_SZ);
				len += snprintf(line_buf+len,
						LPFC_MBX_ACC_LBUF_SZ-len,
						"%03d: ", i);
			}
			len += snprintf(line_buf+len, LPFC_MBX_ACC_LBUF_SZ-len,
					"%08x ",
					((uint32_t)*pword) & 0xffffffff);
			pword++;
		}
		if ((i - 1) % 8)
			pr_err("%s\n", line_buf);
		pr_err("\n");
	}
	if (*mbx_dump_map & LPFC_MBX_DMP_MBX_BYTE) {
		pr_err("Mailbox command:0x%x dump by byte:\n",
		       pmbox->mbxCommand);
		pbyte = (uint8_t *)pmbox;
		for (i = 0; i < *mbx_word_cnt; i++) {
			if (!(i % 8)) {
				if (i != 0)
					pr_err("%s\n", line_buf);
				len = 0;
				memset(line_buf, 0, LPFC_MBX_ACC_LBUF_SZ);
				len += snprintf(line_buf+len,
						LPFC_MBX_ACC_LBUF_SZ-len,
						"%03d: ", i);
			}
			for (j = 0; j < 4; j++) {
				len += snprintf(line_buf+len,
						LPFC_MBX_ACC_LBUF_SZ-len,
						"%02x",
						((uint8_t)*pbyte) & 0xff);
				pbyte++;
			}
			len += snprintf(line_buf+len,
					LPFC_MBX_ACC_LBUF_SZ-len, " ");
		}
		if ((i - 1) % 8)
			pr_err("%s\n", line_buf);
		pr_err("\n");
	}
	(*mbx_dump_cnt)--;

	/* Clean out command structure on reaching dump count */
	if (*mbx_dump_cnt == 0)
		memset(&idiag, 0, sizeof(idiag));
	return;
#endif
}