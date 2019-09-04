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
struct tcon_link {int dummy; } ;
struct cifs_pending_open {struct tcon_link* tlink; } ;
struct cifs_fid {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  open_file_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  cifs_add_pending_open_locked (struct cifs_fid*,struct tcon_link*,struct cifs_pending_open*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* tlink_tcon (struct tcon_link*) ; 

void
cifs_add_pending_open(struct cifs_fid *fid, struct tcon_link *tlink,
		      struct cifs_pending_open *open)
{
	spin_lock(&tlink_tcon(tlink)->open_file_lock);
	cifs_add_pending_open_locked(fid, tlink, open);
	spin_unlock(&tlink_tcon(open->tlink)->open_file_lock);
}