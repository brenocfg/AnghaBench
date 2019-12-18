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
struct platform_device {int dummy; } ;
struct mtd_info {int dummy; } ;
struct ar934x_nfc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ar934x_nfc_free_buf (struct ar934x_nfc*) ; 
 struct mtd_info* ar934x_nfc_to_mtd (struct ar934x_nfc*) ; 
 int /*<<< orphan*/  nand_release (struct mtd_info*) ; 
 struct ar934x_nfc* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ar934x_nfc_remove(struct platform_device *pdev)
{
	struct ar934x_nfc *nfc;
	struct mtd_info *mtd;

	nfc = platform_get_drvdata(pdev);
	if (nfc) {
		mtd = ar934x_nfc_to_mtd(nfc);
		nand_release(mtd);
		ar934x_nfc_free_buf(nfc);
	}

	return 0;
}