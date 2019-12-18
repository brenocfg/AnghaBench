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
struct nlm_host {int h_inuse; int /*<<< orphan*/ * net; } ;

/* Variables and functions */

__attribute__((used)) static int
nlmsvc_mark_host(void *data, struct nlm_host *hint)
{
	struct nlm_host *host = data;

	if ((hint->net == NULL) ||
	    (host->net == hint->net))
		host->h_inuse = 1;
	return 0;
}