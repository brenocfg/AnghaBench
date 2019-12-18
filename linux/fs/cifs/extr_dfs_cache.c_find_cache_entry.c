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
struct dfs_cache_entry {int dummy; } ;

/* Variables and functions */
 struct dfs_cache_entry* __find_cache_entry (unsigned int,char const*) ; 
 unsigned int cache_entry_hash (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static inline struct dfs_cache_entry *find_cache_entry(const char *path,
						       unsigned int *hash)
{
	*hash = cache_entry_hash(path, strlen(path));
	return __find_cache_entry(*hash, path);
}