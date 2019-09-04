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
struct alauda_card_info {unsigned char id; } ;

/* Variables and functions */
 struct alauda_card_info* alauda_card_ids ; 

__attribute__((used)) static struct alauda_card_info *alauda_card_find_id(unsigned char id)
{
	int i;

	for (i = 0; alauda_card_ids[i].id != 0; i++)
		if (alauda_card_ids[i].id == id)
			return &(alauda_card_ids[i]);
	return NULL;
}