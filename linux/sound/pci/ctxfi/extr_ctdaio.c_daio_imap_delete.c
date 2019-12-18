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
struct imapper {int dummy; } ;
struct daio_mgr {int init_imap_added; int /*<<< orphan*/  imap_lock; int /*<<< orphan*/  init_imap; int /*<<< orphan*/  imappers; } ;

/* Variables and functions */
 int /*<<< orphan*/  daio_map_op ; 
 int /*<<< orphan*/  input_mapper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct daio_mgr*) ; 
 int input_mapper_delete (int /*<<< orphan*/ *,struct imapper*,int /*<<< orphan*/ ,struct daio_mgr*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int daio_imap_delete(struct daio_mgr *mgr, struct imapper *entry)
{
	unsigned long flags;
	int err;

	spin_lock_irqsave(&mgr->imap_lock, flags);
	err = input_mapper_delete(&mgr->imappers, entry, daio_map_op, mgr);
	if (list_empty(&mgr->imappers)) {
		input_mapper_add(&mgr->imappers, mgr->init_imap,
							daio_map_op, mgr);
		mgr->init_imap_added = 1;
	}
	spin_unlock_irqrestore(&mgr->imap_lock, flags);

	return err;
}