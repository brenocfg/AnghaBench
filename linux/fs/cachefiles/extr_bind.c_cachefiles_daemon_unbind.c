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
struct TYPE_2__ {int /*<<< orphan*/  identifier; } ;
struct cachefiles_cache {int /*<<< orphan*/  tag; int /*<<< orphan*/  secctx; int /*<<< orphan*/  rootdirname; int /*<<< orphan*/  mnt; int /*<<< orphan*/  graveyard; TYPE_1__ cache; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHEFILES_READY ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  dput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscache_withdraw_cache (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mntput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void cachefiles_daemon_unbind(struct cachefiles_cache *cache)
{
	_enter("");

	if (test_bit(CACHEFILES_READY, &cache->flags)) {
		pr_info("File cache on %s unregistering\n",
			cache->cache.identifier);

		fscache_withdraw_cache(&cache->cache);
	}

	dput(cache->graveyard);
	mntput(cache->mnt);

	kfree(cache->rootdirname);
	kfree(cache->secctx);
	kfree(cache->tag);

	_leave("");
}