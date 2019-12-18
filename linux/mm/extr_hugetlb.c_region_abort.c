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
struct resv_map {int /*<<< orphan*/  lock; int /*<<< orphan*/  adds_in_progress; int /*<<< orphan*/  region_cache_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void region_abort(struct resv_map *resv, long f, long t)
{
	spin_lock(&resv->lock);
	VM_BUG_ON(!resv->region_cache_count);
	resv->adds_in_progress--;
	spin_unlock(&resv->lock);
}