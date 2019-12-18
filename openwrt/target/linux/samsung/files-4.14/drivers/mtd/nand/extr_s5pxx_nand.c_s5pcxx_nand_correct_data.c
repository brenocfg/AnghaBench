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
typedef  int u8 ;
typedef  int u32 ;
struct s5p_nand_host {scalar_t__ ecc_base; } ;
struct nand_chip {struct s5p_nand_host* priv; } ;
struct mtd_info {struct nand_chip* priv; } ;

/* Variables and functions */
 scalar_t__ S5P_NFECCERL ; 
 scalar_t__ S5P_NFECCERP ; 
 scalar_t__ S5P_NFECCSECSTAT ; 
 scalar_t__ S5P_NFECCSTAT ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int s5pcxx_nand_correct_data(struct mtd_info *mtd, u8 *dat,
				     u8 *read_ecc, u8 *calc_ecc)
{
	int ret = 0;
    u32 errNo;
    u32 erl0, erl1, erl2, erl3, erp0, erp1;
    struct nand_chip *chip = mtd->priv;
	struct s5p_nand_host *host = chip->priv;
 
    /* Wait until the 8-bit ECC decoding engine is Idle */
    while (readl(host->ecc_base + S5P_NFECCSTAT) & (1 << 31));
     
    errNo = readl(host->ecc_base + S5P_NFECCSECSTAT) & 0x1F;
    erl0 = readl(host->ecc_base + S5P_NFECCERL);
    erl1 = readl(host->ecc_base + S5P_NFECCERL + 0x04);
    erl2 = readl(host->ecc_base + S5P_NFECCERL + 0x08);
    erl3 = readl(host->ecc_base + S5P_NFECCERL + 0x0C);
     
    erp0 = readl(host->ecc_base + S5P_NFECCERP);
    erp1 = readl(host->ecc_base + S5P_NFECCERP + 0x04);
     
    switch (errNo) {
    case 8:
        dat[(erl3 >> 16) & 0x3FF] ^= (erp1 >> 24) & 0xFF;
    case 7:
        dat[erl3 & 0x3FF] ^= (erp1 >> 16) & 0xFF;
    case 6:
        dat[(erl2 >> 16) & 0x3FF] ^= (erp1 >> 8) & 0xFF;
    case 5:
        dat[erl2 & 0x3FF] ^= erp1 & 0xFF;
    case 4:
        dat[(erl1 >> 16) & 0x3FF] ^= (erp0 >> 24) & 0xFF;
    case 3:
        dat[erl1 & 0x3FF] ^= (erp0 >> 16) & 0xFF;
    case 2:
        dat[(erl0 >> 16) & 0x3FF] ^= (erp0 >> 8) & 0xFF;
    case 1:
        dat[erl0 & 0x3FF] ^= erp0 & 0xFF;
    case 0:
        break;
    default:
        ret = -1;
        printk("ECC uncorrectable error detected:%d\n", errNo);
        break;
    }
     
    return ret;
}