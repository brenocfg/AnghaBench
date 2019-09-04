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
typedef  int /*<<< orphan*/  u32 ;
struct desc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void debug_desc(u32 phys, struct desc *desc)
{
#if DEBUG_DESC
	printk(KERN_DEBUG "%X: %X %3X %3X %08X %X %X\n",
	       phys, desc->next, desc->buf_len, desc->pkt_len,
	       desc->data, desc->status, desc->error_count);
#endif
}