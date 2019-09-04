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
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_hba {int dummy; } ;
struct lpfc_dmabuf {int dummy; } ;
typedef  enum sta_type { ____Placeholder_sta_type } sta_type ;
typedef  enum nemb_type { ____Placeholder_nemb_type } nemb_type ;
typedef  enum mbox_type { ____Placeholder_mbox_type } mbox_type ;
typedef  enum dma_type { ____Placeholder_dma_type } dma_type ;

/* Variables and functions */

void
lpfc_idiag_mbxacc_dump_bsg_mbox(struct lpfc_hba *phba, enum nemb_type nemb_tp,
				enum mbox_type mbox_tp, enum dma_type dma_tp,
				enum sta_type sta_tp,
				struct lpfc_dmabuf *dmabuf, uint32_t ext_buf)
{
#ifdef CONFIG_SCSI_LPFC_DEBUG_FS
	uint32_t *mbx_mbox_cmd, *mbx_dump_map, *mbx_dump_cnt, *mbx_word_cnt;
	char line_buf[LPFC_MBX_ACC_LBUF_SZ];
	int len = 0;
	uint32_t do_dump = 0;
	uint32_t *pword;
	uint32_t i;

	if (idiag.cmd.opcode != LPFC_IDIAG_BSG_MBXACC_DP)
		return;

	mbx_mbox_cmd = &idiag.cmd.data[IDIAG_MBXACC_MBCMD_INDX];
	mbx_dump_map = &idiag.cmd.data[IDIAG_MBXACC_DPMAP_INDX];
	mbx_dump_cnt = &idiag.cmd.data[IDIAG_MBXACC_DPCNT_INDX];
	mbx_word_cnt = &idiag.cmd.data[IDIAG_MBXACC_WDCNT_INDX];

	if (!(*mbx_dump_map & LPFC_MBX_DMP_ALL) ||
	    (*mbx_dump_cnt == 0) ||
	    (*mbx_word_cnt == 0))
		return;

	if (*mbx_mbox_cmd != 0x9B)
		return;

	if ((mbox_tp == mbox_rd) && (dma_tp == dma_mbox)) {
		if (*mbx_dump_map & LPFC_BSG_DMP_MBX_RD_MBX) {
			do_dump |= LPFC_BSG_DMP_MBX_RD_MBX;
			pr_err("\nRead mbox command (x%x), "
			       "nemb:0x%x, extbuf_cnt:%d:\n",
			       sta_tp, nemb_tp, ext_buf);
		}
	}
	if ((mbox_tp == mbox_rd) && (dma_tp == dma_ebuf)) {
		if (*mbx_dump_map & LPFC_BSG_DMP_MBX_RD_BUF) {
			do_dump |= LPFC_BSG_DMP_MBX_RD_BUF;
			pr_err("\nRead mbox buffer (x%x), "
			       "nemb:0x%x, extbuf_seq:%d:\n",
			       sta_tp, nemb_tp, ext_buf);
		}
	}
	if ((mbox_tp == mbox_wr) && (dma_tp == dma_mbox)) {
		if (*mbx_dump_map & LPFC_BSG_DMP_MBX_WR_MBX) {
			do_dump |= LPFC_BSG_DMP_MBX_WR_MBX;
			pr_err("\nWrite mbox command (x%x), "
			       "nemb:0x%x, extbuf_cnt:%d:\n",
			       sta_tp, nemb_tp, ext_buf);
		}
	}
	if ((mbox_tp == mbox_wr) && (dma_tp == dma_ebuf)) {
		if (*mbx_dump_map & LPFC_BSG_DMP_MBX_WR_BUF) {
			do_dump |= LPFC_BSG_DMP_MBX_WR_BUF;
			pr_err("\nWrite mbox buffer (x%x), "
			       "nemb:0x%x, extbuf_seq:%d:\n",
			       sta_tp, nemb_tp, ext_buf);
		}
	}

	/* dump buffer content */
	if (do_dump) {
		pword = (uint32_t *)dmabuf->virt;
		for (i = 0; i < *mbx_word_cnt; i++) {
			if (!(i % 8)) {
				if (i != 0)
					pr_err("%s\n", line_buf);
				len = 0;
				len += snprintf(line_buf+len,
						LPFC_MBX_ACC_LBUF_SZ-len,
						"%03d: ", i);
			}
			len += snprintf(line_buf+len, LPFC_MBX_ACC_LBUF_SZ-len,
					"%08x ", (uint32_t)*pword);
			pword++;
		}
		if ((i - 1) % 8)
			pr_err("%s\n", line_buf);
		(*mbx_dump_cnt)--;
	}

	/* Clean out command structure on reaching dump count */
	if (*mbx_dump_cnt == 0)
		memset(&idiag, 0, sizeof(idiag));
	return;
#endif
}