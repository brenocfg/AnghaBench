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
union smcd_cdc_cursor {int /*<<< orphan*/  acurs; } ;
struct smc_connection {int /*<<< orphan*/  acurs_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void smcd_curs_copy(union smcd_cdc_cursor *tgt,
				  union smcd_cdc_cursor *src,
				  struct smc_connection *conn)
{
#ifndef KERNEL_HAS_ATOMIC64
	unsigned long flags;

	spin_lock_irqsave(&conn->acurs_lock, flags);
	tgt->acurs = src->acurs;
	spin_unlock_irqrestore(&conn->acurs_lock, flags);
#else
	atomic64_set(&tgt->acurs, atomic64_read(&src->acurs));
#endif
}