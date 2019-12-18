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
struct TYPE_2__ {int /*<<< orphan*/  fid_mutex; void* fid; } ;
struct cifs_tcon {int /*<<< orphan*/  num_remote_opens; int /*<<< orphan*/  num_local_opens; int /*<<< orphan*/  stat_lock; TYPE_1__ crfid; int /*<<< orphan*/  open_file_lock; int /*<<< orphan*/  tcon_list; int /*<<< orphan*/  openFileList; int /*<<< orphan*/  tc_count; int /*<<< orphan*/  tidStatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  CifsNew ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cifs_tcon*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tconInfoAllocCount ; 

struct cifs_tcon *
tconInfoAlloc(void)
{
	struct cifs_tcon *ret_buf;

	ret_buf = kzalloc(sizeof(*ret_buf), GFP_KERNEL);
	if (!ret_buf)
		return NULL;
	ret_buf->crfid.fid = kzalloc(sizeof(*ret_buf->crfid.fid), GFP_KERNEL);
	if (!ret_buf->crfid.fid) {
		kfree(ret_buf);
		return NULL;
	}

	atomic_inc(&tconInfoAllocCount);
	ret_buf->tidStatus = CifsNew;
	++ret_buf->tc_count;
	INIT_LIST_HEAD(&ret_buf->openFileList);
	INIT_LIST_HEAD(&ret_buf->tcon_list);
	spin_lock_init(&ret_buf->open_file_lock);
	mutex_init(&ret_buf->crfid.fid_mutex);
	spin_lock_init(&ret_buf->stat_lock);
	atomic_set(&ret_buf->num_local_opens, 0);
	atomic_set(&ret_buf->num_remote_opens, 0);

	return ret_buf;
}