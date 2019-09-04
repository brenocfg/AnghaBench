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
struct sk_buff {int dummy; } ;

/* Variables and functions */

inline struct sk_buff *_rtw_skb_alloc(u32 sz)
{
#ifdef PLATFORM_LINUX
	return __dev_alloc_skb(sz, in_interrupt() ? GFP_ATOMIC : GFP_KERNEL);
#endif /* PLATFORM_LINUX */

#ifdef PLATFORM_FREEBSD
	return dev_alloc_skb(sz);
#endif /* PLATFORM_FREEBSD */
}