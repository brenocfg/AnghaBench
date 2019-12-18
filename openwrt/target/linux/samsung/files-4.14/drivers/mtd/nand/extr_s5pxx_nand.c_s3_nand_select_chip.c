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
typedef  int /*<<< orphan*/  u32 ;
struct s5p_nand_host {scalar_t__ nf_base; } ;
struct nand_chip {struct s5p_nand_host* priv; } ;
struct mtd_info {struct nand_chip* priv; } ;

/* Variables and functions */
 scalar_t__ S5P_NFCONT ; 
 int /*<<< orphan*/  S5P_NFCONT_nFCE0 ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void s3_nand_select_chip(struct mtd_info *mtd, int chip)
{
	struct nand_chip *nand_chip = mtd->priv;
	struct s5p_nand_host *host = nand_chip->priv;
	u32 value = readl(host->nf_base + S5P_NFCONT);

	if (chip == -1)
		value |= S5P_NFCONT_nFCE0;	/* deselect */
	else
		value &= ~S5P_NFCONT_nFCE0;	/* select */

	writel(value, host->nf_base + S5P_NFCONT);
}