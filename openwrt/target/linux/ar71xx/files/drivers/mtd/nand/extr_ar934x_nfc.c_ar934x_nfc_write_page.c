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
typedef  int /*<<< orphan*/  u8 ;
struct nand_chip {int /*<<< orphan*/  oob_poi; } ;
struct mtd_info {int /*<<< orphan*/  writesize; int /*<<< orphan*/  oobsize; } ;
struct ar934x_nfc {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_CMD_PAGEPROG ; 
 int /*<<< orphan*/  ar934x_nfc_disable_hwecc (struct ar934x_nfc*) ; 
 int /*<<< orphan*/  ar934x_nfc_enable_hwecc (struct ar934x_nfc*) ; 
 int ar934x_nfc_send_write (struct ar934x_nfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ar934x_nfc_write_oob (struct mtd_info*,struct nand_chip*,int) ; 
 int /*<<< orphan*/  is_all_ff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct ar934x_nfc* mtd_to_ar934x_nfc (struct mtd_info*) ; 
 int /*<<< orphan*/  nfc_dbg (struct ar934x_nfc*,char*,int,int) ; 

__attribute__((used)) static int
ar934x_nfc_write_page(struct mtd_info *mtd, struct nand_chip *chip,
		      const u8 *buf, int oob_required, int page)
{
	struct ar934x_nfc *nfc = mtd_to_ar934x_nfc(mtd);
	int err;

	nfc_dbg(nfc, "write_page: page:%d oob:%d\n", page, oob_required);

	/* write OOB first */
	if (oob_required &&
	    !is_all_ff(chip->oob_poi, mtd->oobsize)) {
		err = ar934x_nfc_write_oob(mtd, chip, page);
		if (err)
			return err;
	}

	/* TODO: optimize to avoid memcopy */
	memcpy(nfc->buf, buf, mtd->writesize);

	ar934x_nfc_enable_hwecc(nfc);
	err = ar934x_nfc_send_write(nfc, NAND_CMD_PAGEPROG, 0, page,
				    mtd->writesize);
	ar934x_nfc_disable_hwecc(nfc);

	return err;
}