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
struct fscache_cookie {int /*<<< orphan*/  usage; } ;
typedef  enum fscache_cookie_trace { ____Placeholder_fscache_cookie_trace } fscache_cookie_trace ;

/* Variables and functions */
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_fscache_cookie (struct fscache_cookie*,int,int) ; 

__attribute__((used)) static inline void fscache_cookie_get(struct fscache_cookie *cookie,
				      enum fscache_cookie_trace where)
{
	int usage = atomic_inc_return(&cookie->usage);

	trace_fscache_cookie(cookie, where, usage);
}