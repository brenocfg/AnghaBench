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
typedef  int u32 ;

/* Variables and functions */
 int GB_SDIO_VDD_165_195 ; 
 int GB_SDIO_VDD_20_21 ; 
 int GB_SDIO_VDD_21_22 ; 
 int GB_SDIO_VDD_22_23 ; 
 int GB_SDIO_VDD_23_24 ; 
 int GB_SDIO_VDD_24_25 ; 
 int GB_SDIO_VDD_25_26 ; 
 int GB_SDIO_VDD_26_27 ; 
 int GB_SDIO_VDD_27_28 ; 
 int GB_SDIO_VDD_28_29 ; 
 int GB_SDIO_VDD_29_30 ; 
 int GB_SDIO_VDD_30_31 ; 
 int GB_SDIO_VDD_31_32 ; 
 int GB_SDIO_VDD_32_33 ; 
 int GB_SDIO_VDD_33_34 ; 
 int GB_SDIO_VDD_34_35 ; 
 int GB_SDIO_VDD_35_36 ; 
 int MMC_VDD_165_195 ; 
 int MMC_VDD_20_21 ; 
 int MMC_VDD_21_22 ; 
 int MMC_VDD_22_23 ; 
 int MMC_VDD_23_24 ; 
 int MMC_VDD_24_25 ; 
 int MMC_VDD_25_26 ; 
 int MMC_VDD_26_27 ; 
 int MMC_VDD_27_28 ; 
 int MMC_VDD_28_29 ; 
 int MMC_VDD_29_30 ; 
 int MMC_VDD_30_31 ; 
 int MMC_VDD_31_32 ; 
 int MMC_VDD_32_33 ; 
 int MMC_VDD_33_34 ; 
 int MMC_VDD_34_35 ; 
 int MMC_VDD_35_36 ; 

__attribute__((used)) static u32 _gb_sdio_get_host_ocr(u32 ocr)
{
	return (((ocr & GB_SDIO_VDD_165_195) ? MMC_VDD_165_195 : 0) |
		((ocr & GB_SDIO_VDD_20_21) ? MMC_VDD_20_21 : 0) |
		((ocr & GB_SDIO_VDD_21_22) ? MMC_VDD_21_22 : 0) |
		((ocr & GB_SDIO_VDD_22_23) ? MMC_VDD_22_23 : 0) |
		((ocr & GB_SDIO_VDD_23_24) ? MMC_VDD_23_24 : 0) |
		((ocr & GB_SDIO_VDD_24_25) ? MMC_VDD_24_25 : 0) |
		((ocr & GB_SDIO_VDD_25_26) ? MMC_VDD_25_26 : 0) |
		((ocr & GB_SDIO_VDD_26_27) ? MMC_VDD_26_27 : 0) |
		((ocr & GB_SDIO_VDD_27_28) ? MMC_VDD_27_28 : 0) |
		((ocr & GB_SDIO_VDD_28_29) ? MMC_VDD_28_29 : 0) |
		((ocr & GB_SDIO_VDD_29_30) ? MMC_VDD_29_30 : 0) |
		((ocr & GB_SDIO_VDD_30_31) ? MMC_VDD_30_31 : 0) |
		((ocr & GB_SDIO_VDD_31_32) ? MMC_VDD_31_32 : 0) |
		((ocr & GB_SDIO_VDD_32_33) ? MMC_VDD_32_33 : 0) |
		((ocr & GB_SDIO_VDD_33_34) ? MMC_VDD_33_34 : 0) |
		((ocr & GB_SDIO_VDD_34_35) ? MMC_VDD_34_35 : 0) |
		((ocr & GB_SDIO_VDD_35_36) ? MMC_VDD_35_36 : 0)
		);
}