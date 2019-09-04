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
struct file {int dummy; } ;
struct dnotify_struct {scalar_t__ dn_owner; int dn_fd; struct dnotify_struct* dn_next; struct file* dn_filp; int /*<<< orphan*/  dn_mask; } ;
struct dnotify_mark {struct dnotify_struct* dn; } ;
typedef  scalar_t__ fl_owner_t ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int EEXIST ; 

__attribute__((used)) static int attach_dn(struct dnotify_struct *dn, struct dnotify_mark *dn_mark,
		     fl_owner_t id, int fd, struct file *filp, __u32 mask)
{
	struct dnotify_struct *odn;

	odn = dn_mark->dn;
	while (odn != NULL) {
		/* adding more events to existing dnofiy_struct? */
		if ((odn->dn_owner == id) && (odn->dn_filp == filp)) {
			odn->dn_fd = fd;
			odn->dn_mask |= mask;
			return -EEXIST;
		}
		odn = odn->dn_next;
	}

	dn->dn_mask = mask;
	dn->dn_fd = fd;
	dn->dn_filp = filp;
	dn->dn_owner = id;
	dn->dn_next = dn_mark->dn;
	dn_mark->dn = dn;

	return 0;
}