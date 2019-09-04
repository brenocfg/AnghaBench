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
struct module {int dummy; } ;
struct iscsi_session {int /*<<< orphan*/  discovery_parent_type; int /*<<< orphan*/  portal_type; int /*<<< orphan*/  ifacename; int /*<<< orphan*/  boot_target; int /*<<< orphan*/  boot_nic; int /*<<< orphan*/  boot_root; int /*<<< orphan*/  initiatorname; int /*<<< orphan*/  targetalias; int /*<<< orphan*/  targetname; int /*<<< orphan*/  username_in; int /*<<< orphan*/  username; int /*<<< orphan*/  password_in; int /*<<< orphan*/  password; int /*<<< orphan*/  cmdpool; struct Scsi_Host* host; } ;
struct iscsi_cls_session {TYPE_1__* transport; struct iscsi_session* dd_data; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {struct module* owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsi_free_session (struct iscsi_cls_session*) ; 
 int /*<<< orphan*/  iscsi_host_dec_session_cnt (struct Scsi_Host*) ; 
 int /*<<< orphan*/  iscsi_pool_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_remove_session (struct iscsi_cls_session*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 

void iscsi_session_teardown(struct iscsi_cls_session *cls_session)
{
	struct iscsi_session *session = cls_session->dd_data;
	struct module *owner = cls_session->transport->owner;
	struct Scsi_Host *shost = session->host;

	iscsi_pool_free(&session->cmdpool);

	iscsi_remove_session(cls_session);

	kfree(session->password);
	kfree(session->password_in);
	kfree(session->username);
	kfree(session->username_in);
	kfree(session->targetname);
	kfree(session->targetalias);
	kfree(session->initiatorname);
	kfree(session->boot_root);
	kfree(session->boot_nic);
	kfree(session->boot_target);
	kfree(session->ifacename);
	kfree(session->portal_type);
	kfree(session->discovery_parent_type);

	iscsi_free_session(cls_session);

	iscsi_host_dec_session_cnt(shost);
	module_put(owner);
}