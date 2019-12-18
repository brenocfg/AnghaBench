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
struct sock {int dummy; } ;
struct atm_vcc {int /*<<< orphan*/  (* release_cb ) (struct atm_vcc*) ;} ;

/* Variables and functions */
 struct atm_vcc* atm_sk (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct atm_vcc*) ; 

__attribute__((used)) static void vcc_release_cb(struct sock *sk)
{
	struct atm_vcc *vcc = atm_sk(sk);

	if (vcc->release_cb)
		vcc->release_cb(vcc);
}