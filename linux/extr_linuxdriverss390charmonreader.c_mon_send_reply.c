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
struct mon_private {int read_index; int /*<<< orphan*/  read_ready; int /*<<< orphan*/  msglim_count; int /*<<< orphan*/  path; } ;
struct mon_msg {int replied_msglim; scalar_t__ mca_offset; scalar_t__ pos; int /*<<< orphan*/  msglim_reached; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IUCV_IPRMDATA ; 
 int MON_MSGLIM ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int iucv_message_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int mon_send_reply(struct mon_msg *monmsg,
			  struct mon_private *monpriv)
{
	int rc;

	rc = iucv_message_reply(monpriv->path, &monmsg->msg,
				IUCV_IPRMDATA, NULL, 0);
	atomic_dec(&monpriv->msglim_count);
	if (likely(!monmsg->msglim_reached)) {
		monmsg->pos = 0;
		monmsg->mca_offset = 0;
		monpriv->read_index = (monpriv->read_index + 1) %
				      MON_MSGLIM;
		atomic_dec(&monpriv->read_ready);
	} else
		monmsg->replied_msglim = 1;
	if (rc) {
		pr_err("Reading monitor data failed with rc=%i\n", rc);
		return -EIO;
	}
	return 0;
}