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
typedef  int uint32_t ;
struct aic7770_identity {int full_id; int id_mask; } ;

/* Variables and functions */
 int ahc_num_aic7770_devs ; 
 struct aic7770_identity* aic7770_ident_table ; 

struct aic7770_identity *
aic7770_find_device(uint32_t id)
{
	struct	aic7770_identity *entry;
	int	i;

	for (i = 0; i < ahc_num_aic7770_devs; i++) {
		entry = &aic7770_ident_table[i];
		if (entry->full_id == (id & entry->id_mask))
			return (entry);
	}
	return (NULL);
}