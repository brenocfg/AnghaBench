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
struct nlm_host {int /*<<< orphan*/  h_count; int /*<<< orphan*/  h_server; int /*<<< orphan*/  h_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 

void nlmsvc_release_host(struct nlm_host *host)
{
	if (host == NULL)
		return;

	dprintk("lockd: release server host %s\n", host->h_name);

	WARN_ON_ONCE(!host->h_server);
	refcount_dec(&host->h_count);
}