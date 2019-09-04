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
struct dst_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct dst_cache_pcpu {TYPE_1__ in_saddr; } ;
struct dst_cache {int /*<<< orphan*/  cache; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  dst_cache_per_cpu_dst_set (struct dst_cache_pcpu*,struct dst_entry*,int /*<<< orphan*/ ) ; 
 struct dst_cache_pcpu* this_cpu_ptr (int /*<<< orphan*/ ) ; 

void dst_cache_set_ip4(struct dst_cache *dst_cache, struct dst_entry *dst,
		       __be32 saddr)
{
	struct dst_cache_pcpu *idst;

	if (!dst_cache->cache)
		return;

	idst = this_cpu_ptr(dst_cache->cache);
	dst_cache_per_cpu_dst_set(idst, dst, 0);
	idst->in_saddr.s_addr = saddr;
}