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
struct fc_lport {int /*<<< orphan*/  lp_mutex; } ;
struct fc_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_LS_ACC ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_lport_enter_reset (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_seq_els_rsp_send (struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fc_lport_recv_logo_req(struct fc_lport *lport, struct fc_frame *fp)
{
	lockdep_assert_held(&lport->lp_mutex);

	fc_seq_els_rsp_send(fp, ELS_LS_ACC, NULL);
	fc_lport_enter_reset(lport);
	fc_frame_free(fp);
}