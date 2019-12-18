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
struct smb_hdr {int /*<<< orphan*/  Command; } ;
struct mid_q_entry {int /*<<< orphan*/  mid_state; TYPE_1__* callback_data; int /*<<< orphan*/  callback; struct TCP_Server_Info* server; int /*<<< orphan*/  when_alloc; int /*<<< orphan*/  command; int /*<<< orphan*/  pid; int /*<<< orphan*/  mid; int /*<<< orphan*/  refcount; } ;
struct TCP_Server_Info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  MID_REQUEST_ALLOCATED ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  cifs_mid_poolp ; 
 int /*<<< orphan*/  cifs_wake_up_task ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  get_mid (struct smb_hdr const*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct mid_q_entry* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mid_q_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  midCount ; 

struct mid_q_entry *
AllocMidQEntry(const struct smb_hdr *smb_buffer, struct TCP_Server_Info *server)
{
	struct mid_q_entry *temp;

	if (server == NULL) {
		cifs_dbg(VFS, "Null TCP session in AllocMidQEntry\n");
		return NULL;
	}

	temp = mempool_alloc(cifs_mid_poolp, GFP_NOFS);
	memset(temp, 0, sizeof(struct mid_q_entry));
	kref_init(&temp->refcount);
	temp->mid = get_mid(smb_buffer);
	temp->pid = current->pid;
	temp->command = cpu_to_le16(smb_buffer->Command);
	cifs_dbg(FYI, "For smb_command %d\n", smb_buffer->Command);
	/*	do_gettimeofday(&temp->when_sent);*/ /* easier to use jiffies */
	/* when mid allocated can be before when sent */
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
	return temp;
}