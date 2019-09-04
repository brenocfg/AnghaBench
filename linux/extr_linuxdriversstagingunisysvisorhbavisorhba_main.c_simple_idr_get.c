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
struct idr {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  INT_MAX ; 
 int idr_alloc (struct idr*,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int simple_idr_get(struct idr *idrtable, void *p,
				   spinlock_t *lock)
{
	int id;
	unsigned long flags;

	idr_preload(GFP_KERNEL);
	spin_lock_irqsave(lock, flags);
	id = idr_alloc(idrtable, p, 1, INT_MAX, GFP_NOWAIT);
	spin_unlock_irqrestore(lock, flags);
	idr_preload_end();
	/* failure */
	if (id < 0)
		return 0;
	/* idr_alloc() guarantees > 0 */
	return (unsigned int)(id);
}