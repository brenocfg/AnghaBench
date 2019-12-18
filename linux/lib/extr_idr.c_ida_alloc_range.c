#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct ida_bitmap {unsigned long* bitmap; } ;
struct ida {int /*<<< orphan*/  xa; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_11__ {unsigned int xa_index; } ;

/* Variables and functions */
 unsigned int BITS_PER_XA_VALUE ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 unsigned int IDA_BITMAP_BITS ; 
 unsigned int INT_MAX ; 
 int /*<<< orphan*/  XA_FREE_MARK ; 
 int /*<<< orphan*/  XA_STATE (TYPE_1__,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  __set_bit (unsigned int,unsigned long*) ; 
 scalar_t__ bitmap_full (unsigned long*,unsigned int) ; 
 unsigned int find_next_zero_bit (unsigned long*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct ida_bitmap*) ; 
 struct ida_bitmap* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ xa_is_value (struct ida_bitmap*) ; 
 struct ida_bitmap* xa_mk_value (unsigned long) ; 
 unsigned long xa_to_value (struct ida_bitmap*) ; 
 TYPE_1__ xas ; 
 int /*<<< orphan*/  xas_clear_mark (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int xas_error (TYPE_1__*) ; 
 struct ida_bitmap* xas_find_marked (TYPE_1__*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas_lock_irqsave (TYPE_1__*,unsigned long) ; 
 scalar_t__ xas_nomem (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas_set (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  xas_store (TYPE_1__*,struct ida_bitmap*) ; 
 int /*<<< orphan*/  xas_unlock_irqrestore (TYPE_1__*,unsigned long) ; 

int ida_alloc_range(struct ida *ida, unsigned int min, unsigned int max,
			gfp_t gfp)
{
	XA_STATE(xas, &ida->xa, min / IDA_BITMAP_BITS);
	unsigned bit = min % IDA_BITMAP_BITS;
	unsigned long flags;
	struct ida_bitmap *bitmap, *alloc = NULL;

	if ((int)min < 0)
		return -ENOSPC;

	if ((int)max < 0)
		max = INT_MAX;

retry:
	xas_lock_irqsave(&xas, flags);
next:
	bitmap = xas_find_marked(&xas, max / IDA_BITMAP_BITS, XA_FREE_MARK);
	if (xas.xa_index > min / IDA_BITMAP_BITS)
		bit = 0;
	if (xas.xa_index * IDA_BITMAP_BITS + bit > max)
		goto nospc;

	if (xa_is_value(bitmap)) {
		unsigned long tmp = xa_to_value(bitmap);

		if (bit < BITS_PER_XA_VALUE) {
			bit = find_next_zero_bit(&tmp, BITS_PER_XA_VALUE, bit);
			if (xas.xa_index * IDA_BITMAP_BITS + bit > max)
				goto nospc;
			if (bit < BITS_PER_XA_VALUE) {
				tmp |= 1UL << bit;
				xas_store(&xas, xa_mk_value(tmp));
				goto out;
			}
		}
		bitmap = alloc;
		if (!bitmap)
			bitmap = kzalloc(sizeof(*bitmap), GFP_NOWAIT);
		if (!bitmap)
			goto alloc;
		bitmap->bitmap[0] = tmp;
		xas_store(&xas, bitmap);
		if (xas_error(&xas)) {
			bitmap->bitmap[0] = 0;
			goto out;
		}
	}

	if (bitmap) {
		bit = find_next_zero_bit(bitmap->bitmap, IDA_BITMAP_BITS, bit);
		if (xas.xa_index * IDA_BITMAP_BITS + bit > max)
			goto nospc;
		if (bit == IDA_BITMAP_BITS)
			goto next;

		__set_bit(bit, bitmap->bitmap);
		if (bitmap_full(bitmap->bitmap, IDA_BITMAP_BITS))
			xas_clear_mark(&xas, XA_FREE_MARK);
	} else {
		if (bit < BITS_PER_XA_VALUE) {
			bitmap = xa_mk_value(1UL << bit);
		} else {
			bitmap = alloc;
			if (!bitmap)
				bitmap = kzalloc(sizeof(*bitmap), GFP_NOWAIT);
			if (!bitmap)
				goto alloc;
			__set_bit(bit, bitmap->bitmap);
		}
		xas_store(&xas, bitmap);
	}
out:
	xas_unlock_irqrestore(&xas, flags);
	if (xas_nomem(&xas, gfp)) {
		xas.xa_index = min / IDA_BITMAP_BITS;
		bit = min % IDA_BITMAP_BITS;
		goto retry;
	}
	if (bitmap != alloc)
		kfree(alloc);
	if (xas_error(&xas))
		return xas_error(&xas);
	return xas.xa_index * IDA_BITMAP_BITS + bit;
alloc:
	xas_unlock_irqrestore(&xas, flags);
	alloc = kzalloc(sizeof(*bitmap), gfp);
	if (!alloc)
		return -ENOMEM;
	xas_set(&xas, min / IDA_BITMAP_BITS);
	bit = min % IDA_BITMAP_BITS;
	goto retry;
nospc:
	xas_unlock_irqrestore(&xas, flags);
	return -ENOSPC;
}