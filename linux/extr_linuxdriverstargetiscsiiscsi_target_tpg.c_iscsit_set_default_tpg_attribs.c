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
struct iscsi_tpg_attrib {int /*<<< orphan*/  login_keys_workaround; int /*<<< orphan*/  tpg_enabled_sendtargets; int /*<<< orphan*/  fabric_prot_type; int /*<<< orphan*/  t10_pi; int /*<<< orphan*/  default_erl; int /*<<< orphan*/  demo_mode_discovery; int /*<<< orphan*/  prod_mode_write_protect; int /*<<< orphan*/  demo_mode_write_protect; int /*<<< orphan*/  cache_dynamic_acls; int /*<<< orphan*/  generate_node_acls; int /*<<< orphan*/  default_cmdsn_depth; int /*<<< orphan*/  netif_timeout; int /*<<< orphan*/  login_timeout; int /*<<< orphan*/  authentication; } ;
struct iscsi_portal_group {struct iscsi_tpg_attrib tpg_attrib; } ;

/* Variables and functions */
 int /*<<< orphan*/  TA_AUTHENTICATION ; 
 int /*<<< orphan*/  TA_CACHE_DYNAMIC_ACLS ; 
 int /*<<< orphan*/  TA_DEFAULT_CMDSN_DEPTH ; 
 int /*<<< orphan*/  TA_DEFAULT_ERL ; 
 int /*<<< orphan*/  TA_DEFAULT_FABRIC_PROT_TYPE ; 
 int /*<<< orphan*/  TA_DEFAULT_LOGIN_KEYS_WORKAROUND ; 
 int /*<<< orphan*/  TA_DEFAULT_T10_PI ; 
 int /*<<< orphan*/  TA_DEFAULT_TPG_ENABLED_SENDTARGETS ; 
 int /*<<< orphan*/  TA_DEMO_MODE_DISCOVERY ; 
 int /*<<< orphan*/  TA_DEMO_MODE_WRITE_PROTECT ; 
 int /*<<< orphan*/  TA_GENERATE_NODE_ACLS ; 
 int /*<<< orphan*/  TA_LOGIN_TIMEOUT ; 
 int /*<<< orphan*/  TA_NETIF_TIMEOUT ; 
 int /*<<< orphan*/  TA_PROD_MODE_WRITE_PROTECT ; 

__attribute__((used)) static void iscsit_set_default_tpg_attribs(struct iscsi_portal_group *tpg)
{
	struct iscsi_tpg_attrib *a = &tpg->tpg_attrib;

	a->authentication = TA_AUTHENTICATION;
	a->login_timeout = TA_LOGIN_TIMEOUT;
	a->netif_timeout = TA_NETIF_TIMEOUT;
	a->default_cmdsn_depth = TA_DEFAULT_CMDSN_DEPTH;
	a->generate_node_acls = TA_GENERATE_NODE_ACLS;
	a->cache_dynamic_acls = TA_CACHE_DYNAMIC_ACLS;
	a->demo_mode_write_protect = TA_DEMO_MODE_WRITE_PROTECT;
	a->prod_mode_write_protect = TA_PROD_MODE_WRITE_PROTECT;
	a->demo_mode_discovery = TA_DEMO_MODE_DISCOVERY;
	a->default_erl = TA_DEFAULT_ERL;
	a->t10_pi = TA_DEFAULT_T10_PI;
	a->fabric_prot_type = TA_DEFAULT_FABRIC_PROT_TYPE;
	a->tpg_enabled_sendtargets = TA_DEFAULT_TPG_ENABLED_SENDTARGETS;
	a->login_keys_workaround = TA_DEFAULT_LOGIN_KEYS_WORKAROUND;
}