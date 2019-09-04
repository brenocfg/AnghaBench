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
struct nand_flash_dev {unsigned char model_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct nand_flash_dev*) ; 
 struct nand_flash_dev* nand_flash_ids ; 

__attribute__((used)) static struct nand_flash_dev *
nand_find_id(unsigned char id) {
	int i;

	for (i = 0; i < ARRAY_SIZE(nand_flash_ids); i++)
		if (nand_flash_ids[i].model_id == id)
			return &(nand_flash_ids[i]);
	return NULL;
}