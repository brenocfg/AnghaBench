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
struct TYPE_2__ {struct nfs4_file* sc_file; } ;
struct nfs4_ol_stateid {TYPE_1__ st_stid; } ;
struct nfs4_file {int /*<<< orphan*/  fi_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nfs4_file_get_access (struct nfs4_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_access (int /*<<< orphan*/ ,struct nfs4_ol_stateid*) ; 
 scalar_t__ test_access (int /*<<< orphan*/ ,struct nfs4_ol_stateid*) ; 

__attribute__((used)) static void get_lock_access(struct nfs4_ol_stateid *lock_stp, u32 access)
{
	struct nfs4_file *fp = lock_stp->st_stid.sc_file;

	lockdep_assert_held(&fp->fi_lock);

	if (test_access(access, lock_stp))
		return;
	__nfs4_file_get_access(fp, access);
	set_access(access, lock_stp);
}