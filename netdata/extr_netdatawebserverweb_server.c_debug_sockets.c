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
struct TYPE_2__ {int* fds_acl_flags; int /*<<< orphan*/ * fds_names; scalar_t__ opened; } ;
typedef  int /*<<< orphan*/  BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  D_WEB_CLIENT ; 
 int WEB_CLIENT_ACL_BADGE ; 
 int WEB_CLIENT_ACL_DASHBOARD ; 
 int WEB_CLIENT_ACL_MGMT ; 
 int WEB_CLIENT_ACL_NETDATACONF ; 
 int WEB_CLIENT_ACL_NOCHECK ; 
 int WEB_CLIENT_ACL_REGISTRY ; 
 int WEB_CLIENT_ACL_STREAMING ; 
 TYPE_1__ api_sockets ; 
 int /*<<< orphan*/ * buffer_create (int) ; 
 int /*<<< orphan*/  buffer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buffer_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buffer_strcat (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  buffer_tostring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void debug_sockets() {
	BUFFER *wb = buffer_create(256 * sizeof(char));
	int i;

	for(i = 0 ; i < (int)api_sockets.opened ; i++) {
		buffer_strcat(wb, (api_sockets.fds_acl_flags[i] & WEB_CLIENT_ACL_NOCHECK)?"NONE ":"");
		buffer_strcat(wb, (api_sockets.fds_acl_flags[i] & WEB_CLIENT_ACL_DASHBOARD)?"dashboard ":"");
		buffer_strcat(wb, (api_sockets.fds_acl_flags[i] & WEB_CLIENT_ACL_REGISTRY)?"registry ":"");
		buffer_strcat(wb, (api_sockets.fds_acl_flags[i] & WEB_CLIENT_ACL_BADGE)?"badges ":"");
		buffer_strcat(wb, (api_sockets.fds_acl_flags[i] & WEB_CLIENT_ACL_MGMT)?"management ":"");
		buffer_strcat(wb, (api_sockets.fds_acl_flags[i] & WEB_CLIENT_ACL_STREAMING)?"streaming ":"");
		buffer_strcat(wb, (api_sockets.fds_acl_flags[i] & WEB_CLIENT_ACL_NETDATACONF)?"netdata.conf ":"");
		debug(D_WEB_CLIENT, "Socket fd %d name '%s' acl_flags: %s",
			  i,
			  api_sockets.fds_names[i],
			  buffer_tostring(wb));
		buffer_reset(wb);
	}
	buffer_free(wb);
}