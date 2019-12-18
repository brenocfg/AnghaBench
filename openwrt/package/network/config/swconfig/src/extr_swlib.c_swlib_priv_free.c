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
struct nl_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * cache ; 
 int /*<<< orphan*/ * family ; 
 int /*<<< orphan*/ * handle ; 
 int /*<<< orphan*/  nl_cache_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl_object_put (struct nl_object*) ; 
 int /*<<< orphan*/  nl_socket_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
swlib_priv_free(void)
{
	if (family)
		nl_object_put((struct nl_object*)family);
	if (cache)
		nl_cache_free(cache);
	if (handle)
		nl_socket_free(handle);
	family = NULL;
	handle = NULL;
	cache = NULL;
}