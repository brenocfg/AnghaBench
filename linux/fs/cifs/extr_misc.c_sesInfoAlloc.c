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
struct cifs_ses {int /*<<< orphan*/  iface_lock; int /*<<< orphan*/  session_mutex; int /*<<< orphan*/  tcon_list; int /*<<< orphan*/  smb_ses_list; int /*<<< orphan*/  ses_count; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CifsNew ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct cifs_ses* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sesInfoAllocCount ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct cifs_ses *
sesInfoAlloc(void)
{
	struct cifs_ses *ret_buf;

	ret_buf = kzalloc(sizeof(struct cifs_ses), GFP_KERNEL);
	if (ret_buf) {
		atomic_inc(&sesInfoAllocCount);
		ret_buf->status = CifsNew;
		++ret_buf->ses_count;
		INIT_LIST_HEAD(&ret_buf->smb_ses_list);
		INIT_LIST_HEAD(&ret_buf->tcon_list);
		mutex_init(&ret_buf->session_mutex);
		spin_lock_init(&ret_buf->iface_lock);
	}
	return ret_buf;
}