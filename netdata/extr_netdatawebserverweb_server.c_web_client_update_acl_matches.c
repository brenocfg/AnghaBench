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
struct web_client {int /*<<< orphan*/  port_acl; int /*<<< orphan*/  acl; int /*<<< orphan*/  client_ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  WEB_CLIENT_ACL_BADGE ; 
 int /*<<< orphan*/  WEB_CLIENT_ACL_DASHBOARD ; 
 int /*<<< orphan*/  WEB_CLIENT_ACL_MGMT ; 
 int /*<<< orphan*/  WEB_CLIENT_ACL_NETDATACONF ; 
 int /*<<< orphan*/  WEB_CLIENT_ACL_NONE ; 
 int /*<<< orphan*/  WEB_CLIENT_ACL_REGISTRY ; 
 int /*<<< orphan*/  WEB_CLIENT_ACL_STREAMING ; 
 scalar_t__ simple_pattern_matches (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  web_allow_badges_from ; 
 int /*<<< orphan*/  web_allow_dashboard_from ; 
 int /*<<< orphan*/  web_allow_mgmt_from ; 
 int /*<<< orphan*/  web_allow_netdataconf_from ; 
 int /*<<< orphan*/  web_allow_registry_from ; 
 int /*<<< orphan*/  web_allow_streaming_from ; 

void web_client_update_acl_matches(struct web_client *w) {
    w->acl = WEB_CLIENT_ACL_NONE;

    if(!web_allow_dashboard_from || simple_pattern_matches(web_allow_dashboard_from, w->client_ip))
        w->acl |= WEB_CLIENT_ACL_DASHBOARD;

    if(!web_allow_registry_from || simple_pattern_matches(web_allow_registry_from, w->client_ip))
        w->acl |= WEB_CLIENT_ACL_REGISTRY;

    if(!web_allow_badges_from || simple_pattern_matches(web_allow_badges_from, w->client_ip))
        w->acl |= WEB_CLIENT_ACL_BADGE;

    if(!web_allow_mgmt_from || simple_pattern_matches(web_allow_mgmt_from, w->client_ip))
        w->acl |= WEB_CLIENT_ACL_MGMT;

    if(!web_allow_streaming_from || simple_pattern_matches(web_allow_streaming_from, w->client_ip))
        w->acl |= WEB_CLIENT_ACL_STREAMING;

    if(!web_allow_netdataconf_from || simple_pattern_matches(web_allow_netdataconf_from, w->client_ip))
        w->acl |= WEB_CLIENT_ACL_NETDATACONF;

    w->acl &= w->port_acl;
}