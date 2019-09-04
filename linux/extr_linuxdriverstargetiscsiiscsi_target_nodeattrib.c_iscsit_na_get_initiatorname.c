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
struct se_node_acl {char* initiatorname; } ;
struct iscsi_node_acl {struct se_node_acl se_node_acl; } ;

/* Variables and functions */

__attribute__((used)) static inline char *iscsit_na_get_initiatorname(
	struct iscsi_node_acl *nacl)
{
	struct se_node_acl *se_nacl = &nacl->se_node_acl;

	return &se_nacl->initiatorname[0];
}