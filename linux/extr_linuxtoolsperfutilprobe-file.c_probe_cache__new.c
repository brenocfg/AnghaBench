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
struct probe_cache {int dummy; } ;
struct nsinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 struct probe_cache* probe_cache__alloc () ; 
 int /*<<< orphan*/  probe_cache__delete (struct probe_cache*) ; 
 int probe_cache__load (struct probe_cache*) ; 
 int probe_cache__open (struct probe_cache*,char const*,struct nsinfo*) ; 

struct probe_cache *probe_cache__new(const char *target, struct nsinfo *nsi)
{
	struct probe_cache *pcache = probe_cache__alloc();
	int ret;

	if (!pcache)
		return NULL;

	ret = probe_cache__open(pcache, target, nsi);
	if (ret < 0) {
		pr_debug("Cache open error: %d\n", ret);
		goto out_err;
	}

	ret = probe_cache__load(pcache);
	if (ret < 0) {
		pr_debug("Cache read error: %d\n", ret);
		goto out_err;
	}

	return pcache;

out_err:
	probe_cache__delete(pcache);
	return NULL;
}