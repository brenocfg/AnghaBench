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
struct nand_chip {int /*<<< orphan*/  oob_poi; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; int /*<<< orphan*/  writesize; } ;
struct ar934x_nfc {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_CMD_READ0 ; 
 int ar934x_nfc_send_read (struct ar934x_nfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ar934x_nfc* mtd_to_ar934x_nfc (struct mtd_info*) ; 
 int /*<<< orphan*/  nfc_dbg (struct ar934x_nfc*,char*,int) ; 

__attribute__((used)) static int
ar934x_nfc_read_oob(struct mtd_info *mtd, struct nand_chip *chip,
		    int page)
{
	struct ar934x_nfc *nfc = mtd_to_ar934x_nfc(mtd);
	int err;

	nfc_dbg(nfc, "read_oob: page:%d\n", page);

	err = ar934x_nfc_send_read(nfc, NAND_CMD_READ0, mtd->writesize, page,
				   mtd->oobsize);
	if (err)
		return err;

	memcpy(chip->oob_poi, nfc->buf, mtd->oobsize);

	return 0;
}