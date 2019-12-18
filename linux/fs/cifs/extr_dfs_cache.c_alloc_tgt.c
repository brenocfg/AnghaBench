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
struct dfs_cache_tgt {int /*<<< orphan*/  t_list; int /*<<< orphan*/  t_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct dfs_cache_tgt* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dfs_cache_tgt*) ; 
 struct dfs_cache_tgt* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstrndup (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static inline struct dfs_cache_tgt *alloc_tgt(const char *name)
{
	struct dfs_cache_tgt *t;

	t = kmalloc(sizeof(*t), GFP_KERNEL);
	if (!t)
		return ERR_PTR(-ENOMEM);
	t->t_name = kstrndup(name, strlen(name), GFP_KERNEL);
	if (!t->t_name) {
		kfree(t);
		return ERR_PTR(-ENOMEM);
	}
	INIT_LIST_HEAD(&t->t_list);
	return t;
}