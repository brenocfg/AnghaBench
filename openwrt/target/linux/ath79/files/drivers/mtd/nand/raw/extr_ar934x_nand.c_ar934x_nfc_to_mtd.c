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
struct ar934x_nfc {int /*<<< orphan*/  nand_chip; } ;

/* Variables and functions */
 struct mtd_info* nand_to_mtd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mtd_info *ar934x_nfc_to_mtd(struct ar934x_nfc *nfc)
{
	return nand_to_mtd(&nfc->nand_chip);
}