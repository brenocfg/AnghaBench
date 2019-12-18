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
struct ida {int dummy; } ;

/* Variables and functions */
 unsigned long BITS_PER_LONG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IDA_BITMAP_BITS ; 
 int /*<<< orphan*/  IDA_BUG_ON (struct ida*,int) ; 
 unsigned long ida_alloc (struct ida*,int /*<<< orphan*/ ) ; 
 unsigned long ida_alloc_min (struct ida*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_free (struct ida*,unsigned long) ; 
 int /*<<< orphan*/  ida_is_empty (struct ida*) ; 

__attribute__((used)) static void ida_check_conv(struct ida *ida)
{
	unsigned long i;

	for (i = 0; i < IDA_BITMAP_BITS * 2; i += IDA_BITMAP_BITS) {
		IDA_BUG_ON(ida, ida_alloc_min(ida, i + 1, GFP_KERNEL) != i + 1);
		IDA_BUG_ON(ida, ida_alloc_min(ida, i + BITS_PER_LONG,
					GFP_KERNEL) != i + BITS_PER_LONG);
		ida_free(ida, i + 1);
		ida_free(ida, i + BITS_PER_LONG);
		IDA_BUG_ON(ida, !ida_is_empty(ida));
	}

	for (i = 0; i < IDA_BITMAP_BITS * 2; i++)
		IDA_BUG_ON(ida, ida_alloc(ida, GFP_KERNEL) != i);
	for (i = IDA_BITMAP_BITS * 2; i > 0; i--)
		ida_free(ida, i - 1);
	IDA_BUG_ON(ida, !ida_is_empty(ida));

	for (i = 0; i < IDA_BITMAP_BITS + BITS_PER_LONG - 4; i++)
		IDA_BUG_ON(ida, ida_alloc(ida, GFP_KERNEL) != i);
	for (i = IDA_BITMAP_BITS + BITS_PER_LONG - 4; i > 0; i--)
		ida_free(ida, i - 1);
	IDA_BUG_ON(ida, !ida_is_empty(ida));
}