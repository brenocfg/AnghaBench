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
struct cld_upcall {int /*<<< orphan*/  cu_list; struct cld_net* cu_net; } ;
struct cld_net {int /*<<< orphan*/  cn_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct cld_upcall*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_cld_upcall(struct cld_upcall *victim)
{
	struct cld_net *cn = victim->cu_net;

	spin_lock(&cn->cn_lock);
	list_del(&victim->cu_list);
	spin_unlock(&cn->cn_lock);
	kfree(victim);
}