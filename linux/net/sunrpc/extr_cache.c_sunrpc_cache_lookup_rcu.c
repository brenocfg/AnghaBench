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
struct cache_head {int dummy; } ;
struct cache_detail {int dummy; } ;

/* Variables and functions */
 struct cache_head* sunrpc_cache_add_entry (struct cache_detail*,struct cache_head*,int) ; 
 struct cache_head* sunrpc_cache_find_rcu (struct cache_detail*,struct cache_head*,int) ; 

struct cache_head *sunrpc_cache_lookup_rcu(struct cache_detail *detail,
					   struct cache_head *key, int hash)
{
	struct cache_head *ret;

	ret = sunrpc_cache_find_rcu(detail, key, hash);
	if (ret)
		return ret;
	/* Didn't find anything, insert an empty entry */
	return sunrpc_cache_add_entry(detail, key, hash);
}