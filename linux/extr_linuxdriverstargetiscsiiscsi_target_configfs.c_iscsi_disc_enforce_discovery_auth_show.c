#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iscsi_node_auth {int enforce_discovery_auth; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {struct iscsi_node_auth node_auth; } ;
struct TYPE_4__ {TYPE_1__ discovery_acl; } ;

/* Variables and functions */
 TYPE_2__* iscsit_global ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t iscsi_disc_enforce_discovery_auth_show(struct config_item *item,
		char *page)
{
	struct iscsi_node_auth *discovery_auth = &iscsit_global->discovery_acl.node_auth;

	return sprintf(page, "%d\n", discovery_auth->enforce_discovery_auth);
}