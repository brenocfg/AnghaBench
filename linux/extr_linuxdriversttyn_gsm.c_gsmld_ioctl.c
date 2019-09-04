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
struct tty_struct {struct gsm_mux* disc_data; } ;
struct gsm_mux {int /*<<< orphan*/  mtu; int /*<<< orphan*/  mru; int /*<<< orphan*/  ftype; int /*<<< orphan*/  n2; int /*<<< orphan*/  t2; int /*<<< orphan*/  t1; int /*<<< orphan*/  initiator; int /*<<< orphan*/  encoding; int /*<<< orphan*/  adaption; } ;
struct gsm_config {int i; int /*<<< orphan*/  k; int /*<<< orphan*/  mtu; int /*<<< orphan*/  mru; int /*<<< orphan*/  n2; int /*<<< orphan*/  t3; int /*<<< orphan*/  t2; int /*<<< orphan*/  t1; int /*<<< orphan*/  initiator; int /*<<< orphan*/  encapsulation; int /*<<< orphan*/  adaption; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int EFAULT ; 
#define  GSMIOC_GETCONF 129 
#define  GSMIOC_SETCONF 128 
 int /*<<< orphan*/  UIH ; 
 int /*<<< orphan*/  copy_from_user (struct gsm_config*,void*,int) ; 
 int /*<<< orphan*/  copy_to_user (void*,struct gsm_config*,int) ; 
 int gsmld_config (struct tty_struct*,struct gsm_mux*,struct gsm_config*) ; 
 int /*<<< orphan*/  memset (struct gsm_config*,int /*<<< orphan*/ ,int) ; 
 int n_tty_ioctl_helper (struct tty_struct*,struct file*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gsmld_ioctl(struct tty_struct *tty, struct file *file,
		       unsigned int cmd, unsigned long arg)
{
	struct gsm_config c;
	struct gsm_mux *gsm = tty->disc_data;

	switch (cmd) {
	case GSMIOC_GETCONF:
		memset(&c, 0, sizeof(c));
		c.adaption = gsm->adaption;
		c.encapsulation = gsm->encoding;
		c.initiator = gsm->initiator;
		c.t1 = gsm->t1;
		c.t2 = gsm->t2;
		c.t3 = 0;	/* Not supported */
		c.n2 = gsm->n2;
		if (gsm->ftype == UIH)
			c.i = 1;
		else
			c.i = 2;
		pr_debug("Ftype %d i %d\n", gsm->ftype, c.i);
		c.mru = gsm->mru;
		c.mtu = gsm->mtu;
		c.k = 0;
		if (copy_to_user((void *)arg, &c, sizeof(c)))
			return -EFAULT;
		return 0;
	case GSMIOC_SETCONF:
		if (copy_from_user(&c, (void *)arg, sizeof(c)))
			return -EFAULT;
		return gsmld_config(tty, gsm, &c);
	default:
		return n_tty_ioctl_helper(tty, file, cmd, arg);
	}
}