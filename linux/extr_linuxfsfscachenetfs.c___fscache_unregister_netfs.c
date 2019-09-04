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
struct fscache_netfs {int /*<<< orphan*/  name; int /*<<< orphan*/  primary_index; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  fscache_relinquish_cookie (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ) ; 

void __fscache_unregister_netfs(struct fscache_netfs *netfs)
{
	_enter("{%s.%u}", netfs->name, netfs->version);

	fscache_relinquish_cookie(netfs->primary_index, NULL, false);
	pr_notice("Netfs '%s' unregistered from caching\n", netfs->name);

	_leave("");
}