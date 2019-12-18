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
typedef  int kdb_cmdflags_t ;

/* Variables and functions */
 int KDB_ENABLE_ALL ; 
 int KDB_ENABLE_ALWAYS_SAFE ; 
 int KDB_ENABLE_MASK ; 
 int KDB_ENABLE_NO_ARGS_SHIFT ; 

__attribute__((used)) static inline bool kdb_check_flags(kdb_cmdflags_t flags, int permissions,
				   bool no_args)
{
	/* permissions comes from userspace so needs massaging slightly */
	permissions &= KDB_ENABLE_MASK;
	permissions |= KDB_ENABLE_ALWAYS_SAFE;

	/* some commands change group when launched with no arguments */
	if (no_args)
		permissions |= permissions << KDB_ENABLE_NO_ARGS_SHIFT;

	flags |= KDB_ENABLE_ALL;

	return permissions & flags;
}