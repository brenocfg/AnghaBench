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
struct fnic {int /*<<< orphan*/ * io_req_lock; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int FNIC_IO_LOCKS ; 

__attribute__((used)) static inline spinlock_t *fnic_io_lock_tag(struct fnic *fnic,
					    int tag)
{
	return &fnic->io_req_lock[tag & (FNIC_IO_LOCKS - 1)];
}