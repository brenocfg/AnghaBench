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
struct nlm_host {TYPE_1__* h_nsmhandle; scalar_t__ h_server; } ;
struct TYPE_2__ {int sm_sticky; } ;

/* Variables and functions */

__attribute__((used)) static int
nlmsvc_is_client(void *data, struct nlm_host *dummy)
{
	struct nlm_host *host = data;

	if (host->h_server) {
		/* we are destroying locks even though the client
		 * hasn't asked us too, so don't unmonitor the
		 * client
		 */
		if (host->h_nsmhandle)
			host->h_nsmhandle->sm_sticky = 1;
		return 1;
	} else
		return 0;
}