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
struct dfs_cache_tgt {char* t_name; } ;
struct dfs_cache_entry {struct dfs_cache_tgt* ce_tgthint; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 char* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline char *get_tgt_name(const struct dfs_cache_entry *ce)
{
	struct dfs_cache_tgt *t = ce->ce_tgthint;

	return t ? t->t_name : ERR_PTR(-ENOENT);
}