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
struct nfs_delegation {int /*<<< orphan*/ * cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct nfs_delegation*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_cred (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu ; 

__attribute__((used)) static void nfs_free_delegation(struct nfs_delegation *delegation)
{
	put_cred(delegation->cred);
	delegation->cred = NULL;
	kfree_rcu(delegation, rcu);
}