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
struct dst_entry {int dummy; } ;
struct dst_cache {int /*<<< orphan*/  cache; } ;

/* Variables and functions */
 struct dst_entry* dst_cache_per_cpu_get (struct dst_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ ) ; 

struct dst_entry *dst_cache_get(struct dst_cache *dst_cache)
{
	if (!dst_cache->cache)
		return NULL;

	return dst_cache_per_cpu_get(dst_cache, this_cpu_ptr(dst_cache->cache));
}