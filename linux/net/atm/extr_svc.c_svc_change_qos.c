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
struct sock {int sk_err; } ;
struct atm_vcc {int /*<<< orphan*/  flags; int /*<<< orphan*/  local; } ;
struct atm_qos {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_VF_RELEASED ; 
 int /*<<< orphan*/  ATM_VF_WAITING ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EUNATCH ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  as_modify ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigd ; 
 int /*<<< orphan*/  sigd_enq2 (struct atm_vcc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct atm_qos*,int /*<<< orphan*/ ) ; 
 struct sock* sk_atm (struct atm_vcc*) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

int svc_change_qos(struct atm_vcc *vcc, struct atm_qos *qos)
{
	struct sock *sk = sk_atm(vcc);
	DEFINE_WAIT(wait);

	set_bit(ATM_VF_WAITING, &vcc->flags);
	sigd_enq2(vcc, as_modify, NULL, NULL, &vcc->local, qos, 0);
	for (;;) {
		prepare_to_wait(sk_sleep(sk), &wait, TASK_UNINTERRUPTIBLE);
		if (!test_bit(ATM_VF_WAITING, &vcc->flags) ||
		    test_bit(ATM_VF_RELEASED, &vcc->flags) || !sigd) {
			break;
		}
		schedule();
	}
	finish_wait(sk_sleep(sk), &wait);
	if (!sigd)
		return -EUNATCH;
	return -sk->sk_err;
}