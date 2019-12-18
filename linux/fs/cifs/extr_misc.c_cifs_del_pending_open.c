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
struct cifs_pending_open {int /*<<< orphan*/  tlink; int /*<<< orphan*/  olist; } ;
struct TYPE_2__ {int /*<<< orphan*/  open_file_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* tlink_tcon (int /*<<< orphan*/ ) ; 

void
cifs_del_pending_open(struct cifs_pending_open *open)
{
	spin_lock(&tlink_tcon(open->tlink)->open_file_lock);
	list_del(&open->olist);
	spin_unlock(&tlink_tcon(open->tlink)->open_file_lock);
}