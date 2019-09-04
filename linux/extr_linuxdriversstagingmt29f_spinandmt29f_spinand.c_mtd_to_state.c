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
struct spinand_state {int dummy; } ;
struct spinand_info {struct spinand_state* priv; } ;
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct spinand_info* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static inline struct spinand_state *mtd_to_state(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct spinand_info *info = nand_get_controller_data(chip);
	struct spinand_state *state = info->priv;

	return state;
}