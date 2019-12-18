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
union smc_host_cursor {int /*<<< orphan*/  acurs; } ;
typedef  int /*<<< orphan*/  u64 ;
struct smc_connection {int /*<<< orphan*/  acurs_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline u64 smc_curs_read(union smc_host_cursor *curs,
				struct smc_connection *conn)
{
#ifndef KERNEL_HAS_ATOMIC64
	unsigned long flags;
	u64 ret;

	spin_lock_irqsave(&conn->acurs_lock, flags);
	ret = curs->acurs;
	spin_unlock_irqrestore(&conn->acurs_lock, flags);
	return ret;
#else
	return atomic64_read(&curs->acurs);
#endif
}