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
typedef  int /*<<< orphan*/  WEB_CLIENT_ACL ;

/* Variables and functions */
 int /*<<< orphan*/  WEB_CLIENT_ACL_BADGE ; 
 int /*<<< orphan*/  WEB_CLIENT_ACL_DASHBOARD ; 
 int /*<<< orphan*/  WEB_CLIENT_ACL_MGMT ; 
 int /*<<< orphan*/  WEB_CLIENT_ACL_NETDATACONF ; 
 int /*<<< orphan*/  WEB_CLIENT_ACL_REGISTRY ; 
 int /*<<< orphan*/  WEB_CLIENT_ACL_STREAMING ; 
 int /*<<< orphan*/  socket_ssl_acl (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

WEB_CLIENT_ACL read_acl(char *st) {
    WEB_CLIENT_ACL ret = socket_ssl_acl(st);

    if (!strcmp(st,"dashboard")) ret |= WEB_CLIENT_ACL_DASHBOARD;
    if (!strcmp(st,"registry")) ret |= WEB_CLIENT_ACL_REGISTRY;
    if (!strcmp(st,"badges")) ret |= WEB_CLIENT_ACL_BADGE;
    if (!strcmp(st,"management")) ret |= WEB_CLIENT_ACL_MGMT;
    if (!strcmp(st,"streaming")) ret |= WEB_CLIENT_ACL_STREAMING;
    if (!strcmp(st,"netdata.conf")) ret |= WEB_CLIENT_ACL_NETDATACONF;

    return ret;
}