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
struct fscache_cookie {int /*<<< orphan*/  netfs_data; TYPE_1__* def; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_context ) (int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static inline
void *fscache_get_context(struct fscache_cookie *cookie, void *context)
{
	if (cookie->def->get_context)
		cookie->def->get_context(cookie->netfs_data, context);
	return context;
}