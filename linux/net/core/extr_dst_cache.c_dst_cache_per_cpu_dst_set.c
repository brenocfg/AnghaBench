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
struct dst_entry {int dummy; } ;
struct dst_cache_pcpu {struct dst_entry* dst; int /*<<< orphan*/  cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_hold (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 

__attribute__((used)) static void dst_cache_per_cpu_dst_set(struct dst_cache_pcpu *dst_cache,
				      struct dst_entry *dst, u32 cookie)
{
	dst_release(dst_cache->dst);
	if (dst)
		dst_hold(dst);

	dst_cache->cookie = cookie;
	dst_cache->dst = dst;
}