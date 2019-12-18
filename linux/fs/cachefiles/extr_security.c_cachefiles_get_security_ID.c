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
struct cred {int dummy; } ;
struct cachefiles_cache {struct cred* cache_cred; int /*<<< orphan*/  secctx; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 struct cred* prepare_kernel_cred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_cred (struct cred*) ; 
 int set_security_override_from_ctx (struct cred*,int /*<<< orphan*/ ) ; 

int cachefiles_get_security_ID(struct cachefiles_cache *cache)
{
	struct cred *new;
	int ret;

	_enter("{%s}", cache->secctx);

	new = prepare_kernel_cred(current);
	if (!new) {
		ret = -ENOMEM;
		goto error;
	}

	if (cache->secctx) {
		ret = set_security_override_from_ctx(new, cache->secctx);
		if (ret < 0) {
			put_cred(new);
			pr_err("Security denies permission to nominate security context: error %d\n",
			       ret);
			goto error;
		}
	}

	cache->cache_cred = new;
	ret = 0;
error:
	_leave(" = %d", ret);
	return ret;
}