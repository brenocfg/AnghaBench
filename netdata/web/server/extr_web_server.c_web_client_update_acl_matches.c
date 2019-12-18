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
struct web_client {int /*<<< orphan*/  port_acl; int /*<<< orphan*/  acl; int /*<<< orphan*/  client_host; int /*<<< orphan*/  client_ip; int /*<<< orphan*/  ifd; } ;

/* Variables and functions */
 int /*<<< orphan*/  WEB_CLIENT_ACL_BADGE ; 
 int /*<<< orphan*/  WEB_CLIENT_ACL_DASHBOARD ; 
 int /*<<< orphan*/  WEB_CLIENT_ACL_MGMT ; 
 int /*<<< orphan*/  WEB_CLIENT_ACL_NETDATACONF ; 
 int /*<<< orphan*/  WEB_CLIENT_ACL_NONE ; 
 int /*<<< orphan*/  WEB_CLIENT_ACL_REGISTRY ; 
 int /*<<< orphan*/  WEB_CLIENT_ACL_STREAMING ; 
 scalar_t__ connection_allowed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  web_allow_badges_dns ; 
 int /*<<< orphan*/  web_allow_badges_from ; 
 int /*<<< orphan*/  web_allow_dashboard_dns ; 
 int /*<<< orphan*/  web_allow_dashboard_from ; 
 int /*<<< orphan*/  web_allow_mgmt_dns ; 
 int /*<<< orphan*/  web_allow_mgmt_from ; 
 int /*<<< orphan*/  web_allow_netdataconf_dns ; 
 int /*<<< orphan*/  web_allow_netdataconf_from ; 
 int /*<<< orphan*/  web_allow_registry_dns ; 
 int /*<<< orphan*/  web_allow_registry_from ; 
 int /*<<< orphan*/  web_allow_streaming_dns ; 
 int /*<<< orphan*/  web_allow_streaming_from ; 

void web_client_update_acl_matches(struct web_client *w) {
    w->acl = WEB_CLIENT_ACL_NONE;

    if (!web_allow_dashboard_from ||
        connection_allowed(w->ifd, w->client_ip, w->client_host, sizeof(w->client_host),
                           web_allow_dashboard_from, "dashboard", web_allow_dashboard_dns))
        w->acl |= WEB_CLIENT_ACL_DASHBOARD;

    if (!web_allow_registry_from ||
        connection_allowed(w->ifd, w->client_ip, w->client_host, sizeof(w->client_host),
                           web_allow_registry_from, "registry", web_allow_registry_dns))
        w->acl |= WEB_CLIENT_ACL_REGISTRY;

    if (!web_allow_badges_from ||
        connection_allowed(w->ifd, w->client_ip, w->client_host, sizeof(w->client_host),
                           web_allow_badges_from, "badges", web_allow_badges_dns))
        w->acl |= WEB_CLIENT_ACL_BADGE;

    if (!web_allow_mgmt_from ||
        connection_allowed(w->ifd, w->client_ip, w->client_host, sizeof(w->client_host),
                           web_allow_mgmt_from, "management", web_allow_mgmt_dns))
        w->acl |= WEB_CLIENT_ACL_MGMT;

    if (!web_allow_streaming_from ||
        connection_allowed(w->ifd, w->client_ip, w->client_host, sizeof(w->client_host),
                           web_allow_streaming_from, "streaming", web_allow_streaming_dns))
        w->acl |= WEB_CLIENT_ACL_STREAMING;

    if (!web_allow_netdataconf_from ||
       connection_allowed(w->ifd, w->client_ip, w->client_host, sizeof(w->client_host),
                          web_allow_netdataconf_from, "netdata.conf", web_allow_netdataconf_dns))
        w->acl |= WEB_CLIENT_ACL_NETDATACONF;

    w->acl &= w->port_acl;
}