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
struct persistent_ram_zone {int flags; int buffer_size; int /*<<< orphan*/  buffer_lock; TYPE_1__* buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int PRZ_FLAG_NO_LOCK ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static size_t buffer_start_add(struct persistent_ram_zone *prz, size_t a)
{
	int old;
	int new;
	unsigned long flags = 0;

	if (!(prz->flags & PRZ_FLAG_NO_LOCK))
		raw_spin_lock_irqsave(&prz->buffer_lock, flags);

	old = atomic_read(&prz->buffer->start);
	new = old + a;
	while (unlikely(new >= prz->buffer_size))
		new -= prz->buffer_size;
	atomic_set(&prz->buffer->start, new);

	if (!(prz->flags & PRZ_FLAG_NO_LOCK))
		raw_spin_unlock_irqrestore(&prz->buffer_lock, flags);

	return old;
}