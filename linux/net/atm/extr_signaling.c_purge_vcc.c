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
struct atm_vcc {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {scalar_t__ sk_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_VF_META ; 
 int /*<<< orphan*/  ATM_VF_REGIS ; 
 int /*<<< orphan*/  ATM_VF_RELEASED ; 
 int /*<<< orphan*/  EUNATCH ; 
 scalar_t__ PF_ATMSVC ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* sk_atm (struct atm_vcc*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcc_release_async (struct atm_vcc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void purge_vcc(struct atm_vcc *vcc)
{
	if (sk_atm(vcc)->sk_family == PF_ATMSVC &&
	    !test_bit(ATM_VF_META, &vcc->flags)) {
		set_bit(ATM_VF_RELEASED, &vcc->flags);
		clear_bit(ATM_VF_REGIS, &vcc->flags);
		vcc_release_async(vcc, -EUNATCH);
	}
}