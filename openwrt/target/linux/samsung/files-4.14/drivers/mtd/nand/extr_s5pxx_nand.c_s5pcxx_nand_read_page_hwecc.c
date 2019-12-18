#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int size; int bytes; int steps; int (* correct ) (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* calculate ) (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* hwctl ) (struct mtd_info*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* read_oob ) (struct mtd_info*,struct nand_chip*,int) ;} ;
struct nand_chip {TYPE_1__ ecc; int /*<<< orphan*/  (* write_buf ) (struct mtd_info*,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* read_buf ) (struct mtd_info*,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* cmdfunc ) (struct mtd_info*,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/ * oob_poi; } ;
struct mtd_oob_region {int offset; } ;
struct TYPE_4__ {int corrected; int /*<<< orphan*/  failed; } ;
struct mtd_info {TYPE_2__ ecc_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_CMD_RNDOUT ; 
 int /*<<< orphan*/  NAND_ECC_READ ; 
 int /*<<< orphan*/  mtd_ooblayout_ecc (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_region*) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,struct nand_chip*,int) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub3 (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct mtd_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub5 (struct mtd_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub6 (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub7 (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s5pcxx_nand_read_page_hwecc(struct mtd_info *mtd, struct nand_chip *chip,
				uint8_t *buf, int oob_required, int page)
{
	struct mtd_oob_region oobregion = { };
 	int i, eccsize = chip->ecc.size;
    int eccbytes = chip->ecc.bytes;
    int eccsteps = chip->ecc.steps;
    uint8_t *oobecc;
    int col, stat;
     
    /* Read the OOB area first */
    chip->ecc.read_oob(mtd, chip, page);
    mtd_ooblayout_ecc(mtd, 0, &oobregion);
 	oobecc = chip->oob_poi + oobregion.offset;

    for (i = 0, col = 0; eccsteps; eccsteps--, i += eccbytes, buf += eccsize, col += eccsize) {
        chip->cmdfunc(mtd, NAND_CMD_RNDOUT, col, -1);
        chip->ecc.hwctl(mtd, NAND_ECC_READ);
        chip->read_buf(mtd, buf, eccsize);
        chip->write_buf(mtd, oobecc + i, eccbytes);
        chip->ecc.calculate(mtd, NULL, NULL);
        stat = chip->ecc.correct(mtd, buf, NULL, NULL);
        if (stat < 0)
            mtd->ecc_stats.failed++;
        else
            mtd->ecc_stats.corrected += stat;
    }
    return 0;
}