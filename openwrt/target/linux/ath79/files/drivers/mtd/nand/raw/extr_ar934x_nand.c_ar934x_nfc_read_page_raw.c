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
struct nand_chip {int /*<<< orphan*/ * oob_poi; } ;
struct mtd_info {int writesize; int oobsize; } ;
struct ar934x_nfc {int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_CMD_READ0 ; 
 int ar934x_nfc_send_read (struct ar934x_nfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct ar934x_nfc* mtd_to_ar934x_nfc (struct mtd_info*) ; 
 int /*<<< orphan*/  nfc_dbg (struct ar934x_nfc*,char*,int,int) ; 

__attribute__((used)) static int ar934x_nfc_read_page_raw(struct mtd_info *mtd,
				    struct nand_chip *chip, u8 *buf,
				    int oob_required, int page)
{
	struct ar934x_nfc *nfc = mtd_to_ar934x_nfc(mtd);
	int len;
	int err;

	nfc_dbg(nfc, "read_page_raw: page:%d oob:%d\n", page, oob_required);

	len = mtd->writesize;
	if (oob_required)
		len += mtd->oobsize;

	err = ar934x_nfc_send_read(nfc, NAND_CMD_READ0, 0, page, len);
	if (err)
		return err;

	memcpy(buf, nfc->buf, mtd->writesize);

	if (oob_required)
		memcpy(chip->oob_poi, &nfc->buf[mtd->writesize], mtd->oobsize);

	return 0;
}