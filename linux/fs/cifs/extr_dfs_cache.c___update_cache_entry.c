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
struct dfs_info3_param {int dummy; } ;
struct dfs_cache_entry {scalar_t__ ce_numtgts; TYPE_1__* ce_tgthint; } ;
struct TYPE_2__ {char* t_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct dfs_cache_entry* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct dfs_cache_entry*) ; 
 int copy_ref_data (struct dfs_info3_param const*,int,struct dfs_cache_entry*,char*) ; 
 struct dfs_cache_entry* find_cache_entry (char const*,unsigned int*) ; 
 int /*<<< orphan*/  free_tgts (struct dfs_cache_entry*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrndup (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static inline struct dfs_cache_entry *
__update_cache_entry(const char *path, const struct dfs_info3_param *refs,
		     int numrefs)
{
	int rc;
	unsigned int h;
	struct dfs_cache_entry *ce;
	char *s, *th = NULL;

	ce = find_cache_entry(path, &h);
	if (IS_ERR(ce))
		return ce;

	if (ce->ce_tgthint) {
		s = ce->ce_tgthint->t_name;
		th = kstrndup(s, strlen(s), GFP_KERNEL);
		if (!th)
			return ERR_PTR(-ENOMEM);
	}

	free_tgts(ce);
	ce->ce_numtgts = 0;

	rc = copy_ref_data(refs, numrefs, ce, th);
	kfree(th);

	if (rc)
		ce = ERR_PTR(rc);

	return ce;
}