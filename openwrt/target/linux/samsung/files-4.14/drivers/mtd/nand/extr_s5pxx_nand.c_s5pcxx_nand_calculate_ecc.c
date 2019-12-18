#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct s5p_nand_host {scalar_t__ ecc_base; scalar_t__ nf_base; } ;
struct TYPE_2__ {int /*<<< orphan*/  bytes; } ;
struct nand_chip {TYPE_1__ ecc; struct s5p_nand_host* priv; } ;
struct mtd_info {struct nand_chip* priv; } ;

/* Variables and functions */
 scalar_t__ S5P_NFCONT ; 
 int /*<<< orphan*/  S5P_NFCONT_MECCLOCK ; 
 scalar_t__ S5P_NFECCPRGECC ; 
 scalar_t__ S5P_NFECCSTAT ; 
 int /*<<< orphan*/  readecc (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  rwl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5pcxx_nand_calculate_ecc(struct mtd_info *mtd, const uint8_t *dat, uint8_t *ecc_code)
{
	struct nand_chip *chip = mtd->priv;
	struct s5p_nand_host *host = chip->priv;

	/* Lock ECC */
	rwl(host->nf_base + S5P_NFCONT, 0, S5P_NFCONT_MECCLOCK);

	if (ecc_code)   /* NAND_ECC_WRITE */ {
		/* ECC encoding is completed  */
		while (!(readl(host->ecc_base + S5P_NFECCSTAT) & (1 << 25)));
		readecc(host->ecc_base + S5P_NFECCPRGECC, ecc_code, chip->ecc.bytes);
	} else {	/* NAND_ECC_READ */
		/* ECC decoding is completed  */
        while (!(readl(host->ecc_base + S5P_NFECCSTAT) & (1 << 24)));
	}

	return 0;
}