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
struct ffs_data {int /*<<< orphan*/  setup_state; } ;
typedef  enum ffs_setup_state { ____Placeholder_ffs_setup_state } ffs_setup_state ;

/* Variables and functions */
 int /*<<< orphan*/  FFS_NO_SETUP ; 
 int /*<<< orphan*/  FFS_SETUP_CANCELLED ; 
 int /*<<< orphan*/  cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline enum ffs_setup_state
ffs_setup_state_clear_cancelled(struct ffs_data *ffs)
{
	return (enum ffs_setup_state)
		cmpxchg(&ffs->setup_state, FFS_SETUP_CANCELLED, FFS_NO_SETUP);
}