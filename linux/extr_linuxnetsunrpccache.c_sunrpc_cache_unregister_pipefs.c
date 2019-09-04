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
struct cache_detail {int /*<<< orphan*/ * pipefs; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_remove_cache_dir (int /*<<< orphan*/ *) ; 

void sunrpc_cache_unregister_pipefs(struct cache_detail *cd)
{
	if (cd->pipefs) {
		rpc_remove_cache_dir(cd->pipefs);
		cd->pipefs = NULL;
	}
}