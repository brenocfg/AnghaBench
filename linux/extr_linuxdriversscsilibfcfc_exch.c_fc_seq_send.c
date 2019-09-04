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
struct fc_seq {int dummy; } ;
struct fc_lport {int dummy; } ;
struct fc_frame {int dummy; } ;
struct fc_exch {int /*<<< orphan*/  ex_lock; } ;

/* Variables and functions */
 struct fc_exch* fc_seq_exch (struct fc_seq*) ; 
 int fc_seq_send_locked (struct fc_lport*,struct fc_seq*,struct fc_frame*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int fc_seq_send(struct fc_lport *lport, struct fc_seq *sp, struct fc_frame *fp)
{
	struct fc_exch *ep;
	int error;
	ep = fc_seq_exch(sp);
	spin_lock_bh(&ep->ex_lock);
	error = fc_seq_send_locked(lport, sp, fp);
	spin_unlock_bh(&ep->ex_lock);
	return error;
}