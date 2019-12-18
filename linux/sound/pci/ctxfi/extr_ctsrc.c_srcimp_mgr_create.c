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
struct srcimp_mgr {int init_imap_added; int /*<<< orphan*/  mgr; int /*<<< orphan*/  card; int /*<<< orphan*/  imap_delete; int /*<<< orphan*/  imap_add; int /*<<< orphan*/  put_srcimp; int /*<<< orphan*/  get_srcimp; struct imapper* init_imap; int /*<<< orphan*/  imappers; int /*<<< orphan*/  imap_lock; int /*<<< orphan*/  mgr_lock; } ;
struct imapper {int /*<<< orphan*/  list; scalar_t__ user; scalar_t__ next; scalar_t__ addr; scalar_t__ slot; } ;
struct hw {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SRCIMP ; 
 int /*<<< orphan*/  SRCIMP_RESOURCE_NUM ; 
 int /*<<< orphan*/  get_srcimp_rsc ; 
 int /*<<< orphan*/  kfree (struct srcimp_mgr*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_srcimp_rsc ; 
 int rsc_mgr_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hw*) ; 
 int /*<<< orphan*/  rsc_mgr_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcimp_imap_add ; 
 int /*<<< orphan*/  srcimp_imap_delete ; 

int srcimp_mgr_create(struct hw *hw, struct srcimp_mgr **rsrcimp_mgr)
{
	int err;
	struct srcimp_mgr *srcimp_mgr;
	struct imapper *entry;

	*rsrcimp_mgr = NULL;
	srcimp_mgr = kzalloc(sizeof(*srcimp_mgr), GFP_KERNEL);
	if (!srcimp_mgr)
		return -ENOMEM;

	err = rsc_mgr_init(&srcimp_mgr->mgr, SRCIMP, SRCIMP_RESOURCE_NUM, hw);
	if (err)
		goto error1;

	spin_lock_init(&srcimp_mgr->mgr_lock);
	spin_lock_init(&srcimp_mgr->imap_lock);
	INIT_LIST_HEAD(&srcimp_mgr->imappers);
	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry) {
		err = -ENOMEM;
		goto error2;
	}
	entry->slot = entry->addr = entry->next = entry->user = 0;
	list_add(&entry->list, &srcimp_mgr->imappers);
	srcimp_mgr->init_imap = entry;
	srcimp_mgr->init_imap_added = 1;

	srcimp_mgr->get_srcimp = get_srcimp_rsc;
	srcimp_mgr->put_srcimp = put_srcimp_rsc;
	srcimp_mgr->imap_add = srcimp_imap_add;
	srcimp_mgr->imap_delete = srcimp_imap_delete;
	srcimp_mgr->card = hw->card;

	*rsrcimp_mgr = srcimp_mgr;

	return 0;

error2:
	rsc_mgr_uninit(&srcimp_mgr->mgr);
error1:
	kfree(srcimp_mgr);
	return err;
}