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

/* Variables and functions */
 unsigned long BITS_PER_XA_VALUE ; 
 int /*<<< orphan*/  DEFINE_IDA (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 unsigned long IDA_BITMAP_BITS ; 
 int /*<<< orphan*/  IDA_BUG_ON (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ida ; 
 int ida_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_destroy (int /*<<< orphan*/ *) ; 

void ida_check_conv_user(void)
{
	DEFINE_IDA(ida);
	unsigned long i;

	for (i = 0; i < 1000000; i++) {
		int id = ida_alloc(&ida, GFP_NOWAIT);
		if (id == -ENOMEM) {
			IDA_BUG_ON(&ida, ((i % IDA_BITMAP_BITS) !=
					  BITS_PER_XA_VALUE) &&
					 ((i % IDA_BITMAP_BITS) != 0));
			id = ida_alloc(&ida, GFP_KERNEL);
		} else {
			IDA_BUG_ON(&ida, (i % IDA_BITMAP_BITS) ==
					BITS_PER_XA_VALUE);
		}
		IDA_BUG_ON(&ida, id != i);
	}
	ida_destroy(&ida);
}