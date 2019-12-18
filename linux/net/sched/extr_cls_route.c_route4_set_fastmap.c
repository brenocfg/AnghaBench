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
typedef  int /*<<< orphan*/  u32 ;
struct route4_head {TYPE_1__* fastmap; } ;
struct route4_filter {int dummy; } ;
struct TYPE_2__ {int iif; struct route4_filter* filter; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  fastmap_lock ; 
 int route4_fastmap_hash (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
route4_set_fastmap(struct route4_head *head, u32 id, int iif,
		   struct route4_filter *f)
{
	int h = route4_fastmap_hash(id, iif);

	/* fastmap updates must look atomic to aling id, iff, filter */
	spin_lock_bh(&fastmap_lock);
	head->fastmap[h].id = id;
	head->fastmap[h].iif = iif;
	head->fastmap[h].filter = f;
	spin_unlock_bh(&fastmap_lock);
}