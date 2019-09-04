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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/ ** ent12_p; } ;
struct fat_entry {int entry; int nr_bhs; struct buffer_head** bhs; TYPE_1__ u; } ;
struct buffer_head {int b_data; int b_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 

__attribute__((used)) static int fat12_ent_next(struct fat_entry *fatent)
{
	u8 **ent12_p = fatent->u.ent12_p;
	struct buffer_head **bhs = fatent->bhs;
	u8 *nextp = ent12_p[1] + 1 + (fatent->entry & 1);

	fatent->entry++;
	if (fatent->nr_bhs == 1) {
		WARN_ON(ent12_p[0] > (u8 *)(bhs[0]->b_data +
							(bhs[0]->b_size - 2)));
		WARN_ON(ent12_p[1] > (u8 *)(bhs[0]->b_data +
							(bhs[0]->b_size - 1)));
		if (nextp < (u8 *)(bhs[0]->b_data + (bhs[0]->b_size - 1))) {
			ent12_p[0] = nextp - 1;
			ent12_p[1] = nextp;
			return 1;
		}
	} else {
		WARN_ON(ent12_p[0] != (u8 *)(bhs[0]->b_data +
							(bhs[0]->b_size - 1)));
		WARN_ON(ent12_p[1] != (u8 *)bhs[1]->b_data);
		ent12_p[0] = nextp - 1;
		ent12_p[1] = nextp;
		brelse(bhs[0]);
		bhs[0] = bhs[1];
		fatent->nr_bhs = 1;
		return 1;
	}
	ent12_p[0] = NULL;
	ent12_p[1] = NULL;
	return 0;
}