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
typedef  int /*<<< orphan*/  xfs_lsn_t ;
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  atomic64_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_LSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CYCLE_LSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
xlog_crack_atomic_lsn(atomic64_t *lsn, uint *cycle, uint *block)
{
	xfs_lsn_t val = atomic64_read(lsn);

	*cycle = CYCLE_LSN(val);
	*block = BLOCK_LSN(val);
}