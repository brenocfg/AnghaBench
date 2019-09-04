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
struct fscache_cookie {struct fscache_cookie* parent; int /*<<< orphan*/  usage; } ;
typedef  enum fscache_cookie_trace { ____Placeholder_fscache_cookie_trace } fscache_cookie_trace ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  _enter (char*,struct fscache_cookie*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int atomic_dec_return (int /*<<< orphan*/ *) ; 
 int fscache_cookie_put_parent ; 
 int /*<<< orphan*/  fscache_free_cookie (struct fscache_cookie*) ; 
 int /*<<< orphan*/  fscache_unhash_cookie (struct fscache_cookie*) ; 
 int /*<<< orphan*/  trace_fscache_cookie (struct fscache_cookie*,int,int) ; 

void fscache_cookie_put(struct fscache_cookie *cookie,
			enum fscache_cookie_trace where)
{
	struct fscache_cookie *parent;
	int usage;

	_enter("%p", cookie);

	do {
		usage = atomic_dec_return(&cookie->usage);
		trace_fscache_cookie(cookie, where, usage);

		if (usage > 0)
			return;
		BUG_ON(usage < 0);

		parent = cookie->parent;
		fscache_unhash_cookie(cookie);
		fscache_free_cookie(cookie);

		cookie = parent;
		where = fscache_cookie_put_parent;
	} while (cookie);

	_leave("");
}