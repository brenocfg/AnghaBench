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
struct mtd_info {int dummy; } ;
struct ar934x_nfc {int /*<<< orphan*/  (* select_chip ) (int) ;} ;

/* Variables and functions */
 struct ar934x_nfc* mtd_to_ar934x_nfc (struct mtd_info*) ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static void
ar934x_nfc_select_chip(struct mtd_info *mtd, int chip_no)
{
	struct ar934x_nfc *nfc = mtd_to_ar934x_nfc(mtd);

	if (nfc->select_chip)
		nfc->select_chip(chip_no);
}