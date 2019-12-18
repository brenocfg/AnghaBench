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
struct smb2_sync_hdr {int /*<<< orphan*/  Command; int /*<<< orphan*/  SessionId; int /*<<< orphan*/  TreeId; int /*<<< orphan*/  MessageId; int /*<<< orphan*/  CreditCharge; } ;
struct mid_q_entry {unsigned int credits; int /*<<< orphan*/  mid; int /*<<< orphan*/  mid_state; TYPE_1__* callback_data; int /*<<< orphan*/  callback; struct TCP_Server_Info* server; int /*<<< orphan*/  when_alloc; int /*<<< orphan*/  command; int /*<<< orphan*/  pid; int /*<<< orphan*/  refcount; } ;
struct TCP_Server_Info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  MID_REQUEST_ALLOCATED ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cifs_mid_poolp ; 
 int /*<<< orphan*/  cifs_wake_up_task ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct mid_q_entry* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mid_q_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  midCount ; 
 int /*<<< orphan*/  trace_smb3_cmd_enter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mid_q_entry *
smb2_mid_entry_alloc(const struct smb2_sync_hdr *shdr,
		     struct TCP_Server_Info *server)
{
	struct mid_q_entry *temp;
	unsigned int credits = le16_to_cpu(shdr->CreditCharge);

	if (server == NULL) {
		cifs_dbg(VFS, "Null TCP session in smb2_mid_entry_alloc\n");
		return NULL;
	}

	temp = mempool_alloc(cifs_mid_poolp, GFP_NOFS);
	memset(temp, 0, sizeof(struct mid_q_entry));
	kref_init(&temp->refcount);
	temp->mid = le64_to_cpu(shdr->MessageId);
	temp->credits = credits > 0 ? credits : 1;
	temp->pid = current->pid;
	temp->command = shdr->Command; /* Always LE */
	temp->when_alloc = jiffies;
	temp->server = server;

	/*
	 * The default is for the mid to be synchronous, so the
	 * default callback just wakes up the current task.
	 */
	temp->callback = cifs_wake_up_task;
	temp->callback_data = current;

	atomic_inc(&midCount);
	temp->mid_state = MID_REQUEST_ALLOCATED;
	trace_smb3_cmd_enter(shdr->TreeId, shdr->SessionId,
		le16_to_cpu(shdr->Command), temp->mid);
	return temp;
}