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
struct dfs_cache_tgt_iterator {char const* it_name; } ;

/* Variables and functions */

__attribute__((used)) static inline const char *
dfs_cache_get_tgt_name(const struct dfs_cache_tgt_iterator *it)
{
	return it ? it->it_name : NULL;
}