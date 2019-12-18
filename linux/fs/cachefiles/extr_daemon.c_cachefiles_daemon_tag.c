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
struct cachefiles_cache {char* tag; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  _enter (char*,char*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int cachefiles_daemon_tag(struct cachefiles_cache *cache, char *args)
{
	char *tag;

	_enter(",%s", args);

	if (!*args) {
		pr_err("Empty tag specified\n");
		return -EINVAL;
	}

	if (cache->tag)
		return -EEXIST;

	tag = kstrdup(args, GFP_KERNEL);
	if (!tag)
		return -ENOMEM;

	cache->tag = tag;
	return 0;
}