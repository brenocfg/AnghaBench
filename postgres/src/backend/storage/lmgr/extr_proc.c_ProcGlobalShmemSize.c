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
typedef  int /*<<< orphan*/  slock_t ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  PROC_HDR ;
typedef  int /*<<< orphan*/  PGXACT ;
typedef  int /*<<< orphan*/  PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  MaxBackends ; 
 int /*<<< orphan*/  NUM_AUXILIARY_PROCS ; 
 int /*<<< orphan*/  add_size (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  max_prepared_xacts ; 
 int mul_size (int /*<<< orphan*/ ,int) ; 

Size
ProcGlobalShmemSize(void)
{
	Size		size = 0;

	/* ProcGlobal */
	size = add_size(size, sizeof(PROC_HDR));
	/* MyProcs, including autovacuum workers and launcher */
	size = add_size(size, mul_size(MaxBackends, sizeof(PGPROC)));
	/* AuxiliaryProcs */
	size = add_size(size, mul_size(NUM_AUXILIARY_PROCS, sizeof(PGPROC)));
	/* Prepared xacts */
	size = add_size(size, mul_size(max_prepared_xacts, sizeof(PGPROC)));
	/* ProcStructLock */
	size = add_size(size, sizeof(slock_t));

	size = add_size(size, mul_size(MaxBackends, sizeof(PGXACT)));
	size = add_size(size, mul_size(NUM_AUXILIARY_PROCS, sizeof(PGXACT)));
	size = add_size(size, mul_size(max_prepared_xacts, sizeof(PGXACT)));

	return size;
}