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
struct ida_bitmap {int /*<<< orphan*/  bitmap; } ;
struct ida {int /*<<< orphan*/  xa; } ;

/* Variables and functions */
 unsigned int BITS_PER_XA_VALUE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int IDA_BITMAP_BITS ; 
 int /*<<< orphan*/  WARN (int,char*,unsigned int) ; 
 int /*<<< orphan*/  XA_FREE_MARK ; 
 int /*<<< orphan*/  XA_STATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  __clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ bitmap_empty (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct ida_bitmap*) ; 
 int /*<<< orphan*/  test_bit (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ xa_is_value (struct ida_bitmap*) ; 
 int /*<<< orphan*/ * xa_mk_value (unsigned long) ; 
 unsigned long xa_to_value (struct ida_bitmap*) ; 
 int /*<<< orphan*/  xas ; 
 struct ida_bitmap* xas_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xas_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xas_set_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas_store (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xas_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ida_free(struct ida *ida, unsigned int id)
{
	XA_STATE(xas, &ida->xa, id / IDA_BITMAP_BITS);
	unsigned bit = id % IDA_BITMAP_BITS;
	struct ida_bitmap *bitmap;
	unsigned long flags;

	BUG_ON((int)id < 0);

	xas_lock_irqsave(&xas, flags);
	bitmap = xas_load(&xas);

	if (xa_is_value(bitmap)) {
		unsigned long v = xa_to_value(bitmap);
		if (bit >= BITS_PER_XA_VALUE)
			goto err;
		if (!(v & (1UL << bit)))
			goto err;
		v &= ~(1UL << bit);
		if (!v)
			goto delete;
		xas_store(&xas, xa_mk_value(v));
	} else {
		if (!test_bit(bit, bitmap->bitmap))
			goto err;
		__clear_bit(bit, bitmap->bitmap);
		xas_set_mark(&xas, XA_FREE_MARK);
		if (bitmap_empty(bitmap->bitmap, IDA_BITMAP_BITS)) {
			kfree(bitmap);
delete:
			xas_store(&xas, NULL);
		}
	}
	xas_unlock_irqrestore(&xas, flags);
	return;
 err:
	xas_unlock_irqrestore(&xas, flags);
	WARN(1, "ida_free called for id=%d which is not allocated.\n", id);
}