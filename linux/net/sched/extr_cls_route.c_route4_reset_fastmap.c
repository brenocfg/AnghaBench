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
struct route4_head {int /*<<< orphan*/  fastmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  fastmap_lock ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
route4_reset_fastmap(struct route4_head *head)
{
	spin_lock_bh(&fastmap_lock);
	memset(head->fastmap, 0, sizeof(head->fastmap));
	spin_unlock_bh(&fastmap_lock);
}