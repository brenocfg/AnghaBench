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
struct ar934x_nfc_platform_data {int /*<<< orphan*/  (* hw_reset ) (int) ;} ;
struct ar934x_nfc {int ctrl_reg; scalar_t__ small_page; } ;

/* Variables and functions */
 int AR934X_NFC_CTRL_CUSTOM_SIZE_EN ; 
 int AR934X_NFC_GENSEQ_SMALL_PAGE_READ ; 
 int /*<<< orphan*/  AR934X_NFC_REG_CTRL ; 
 int /*<<< orphan*/  AR934X_NFC_REG_DMA_ADDR_OFFS ; 
 int /*<<< orphan*/  AR934X_NFC_REG_GEN_SEQ_CTRL ; 
 int /*<<< orphan*/  AR934X_NFC_REG_MEM_CTRL ; 
 int /*<<< orphan*/  AR934X_NFC_REG_TIME_SEQ ; 
 int /*<<< orphan*/  AR934X_NFC_REG_TIMINGS_ASYN ; 
 int /*<<< orphan*/  AR934X_NFC_REG_TIMINGS_SYN ; 
 int AR934X_NFC_TIME_SEQ_DEFAULT ; 
 int AR934X_NFC_TIMINGS_ASYN_DEFAULT ; 
 int AR934X_NFC_TIMINGS_SYN_DEFAULT ; 
 struct ar934x_nfc_platform_data* ar934x_nfc_get_platform_data (struct ar934x_nfc*) ; 
 int /*<<< orphan*/  ar934x_nfc_wr (struct ar934x_nfc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 

__attribute__((used)) static void
ar934x_nfc_hw_init(struct ar934x_nfc *nfc)
{
	struct ar934x_nfc_platform_data *pdata;

	pdata = ar934x_nfc_get_platform_data(nfc);
	if (pdata->hw_reset) {
		pdata->hw_reset(true);
		pdata->hw_reset(false);
	}

	/*
	 * setup timings
	 * TODO: make it configurable via platform data
	 */
	ar934x_nfc_wr(nfc, AR934X_NFC_REG_TIME_SEQ,
		      AR934X_NFC_TIME_SEQ_DEFAULT);
	ar934x_nfc_wr(nfc, AR934X_NFC_REG_TIMINGS_ASYN,
		      AR934X_NFC_TIMINGS_ASYN_DEFAULT);
	ar934x_nfc_wr(nfc, AR934X_NFC_REG_TIMINGS_SYN,
		      AR934X_NFC_TIMINGS_SYN_DEFAULT);

	/* disable WP on all chips, and select chip 0 */
	ar934x_nfc_wr(nfc, AR934X_NFC_REG_MEM_CTRL, 0xff00);

	ar934x_nfc_wr(nfc, AR934X_NFC_REG_DMA_ADDR_OFFS, 0);

	/* initialize Control register */
	nfc->ctrl_reg = AR934X_NFC_CTRL_CUSTOM_SIZE_EN;
	ar934x_nfc_wr(nfc, AR934X_NFC_REG_CTRL, nfc->ctrl_reg);

	if (nfc->small_page) {
		/*  Setup generic sequence register for small page reads. */
		ar934x_nfc_wr(nfc, AR934X_NFC_REG_GEN_SEQ_CTRL,
			      AR934X_NFC_GENSEQ_SMALL_PAGE_READ);
	}
}