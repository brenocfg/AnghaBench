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
struct aa_load_ent {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct aa_load_ent* kzalloc (int,int /*<<< orphan*/ ) ; 

struct aa_load_ent *aa_load_ent_alloc(void)
{
	struct aa_load_ent *ent = kzalloc(sizeof(*ent), GFP_KERNEL);
	if (ent)
		INIT_LIST_HEAD(&ent->list);
	return ent;
}