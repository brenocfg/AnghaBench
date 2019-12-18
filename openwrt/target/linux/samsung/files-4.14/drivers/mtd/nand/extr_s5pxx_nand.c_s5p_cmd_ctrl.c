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
struct s5p_nand_host {scalar_t__ nf_base; } ;
struct nand_chip {struct s5p_nand_host* priv; } ;
struct mtd_info {struct nand_chip* priv; } ;

/* Variables and functions */
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 scalar_t__ S5P_NFADDR ; 
 scalar_t__ S5P_NFCMD ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void s5p_cmd_ctrl(struct mtd_info *mtd, int dat, unsigned int ctrl)
{
	struct nand_chip *nand_chip = mtd->priv;
	struct s5p_nand_host *host = nand_chip->priv;

	if (dat == NAND_CMD_NONE)
		return;
	
	if (ctrl & NAND_CLE)
		writeb(dat, host->nf_base + S5P_NFCMD);
	else
		writeb(dat, host->nf_base + S5P_NFADDR);
}