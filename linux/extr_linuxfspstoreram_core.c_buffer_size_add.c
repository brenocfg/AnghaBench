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
struct persistent_ram_zone {int flags; size_t buffer_size; int /*<<< orphan*/  buffer_lock; TYPE_1__* buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int PRZ_FLAG_NO_LOCK ; 
 size_t atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void buffer_size_add(struct persistent_ram_zone *prz, size_t a)
{
	size_t old;
	size_t new;
	unsigned long flags = 0;

	if (!(prz->flags & PRZ_FLAG_NO_LOCK))
		raw_spin_lock_irqsave(&prz->buffer_lock, flags);

	old = atomic_read(&prz->buffer->size);
	if (old == prz->buffer_size)
		goto exit;

	new = old + a;
	if (new > prz->buffer_size)
		new = prz->buffer_size;
	atomic_set(&prz->buffer->size, new);

exit:
	if (!(prz->flags & PRZ_FLAG_NO_LOCK))
		raw_spin_unlock_irqrestore(&prz->buffer_lock, flags);
}