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
struct TYPE_2__ {scalar_t__ si_exp; } ;
union nfsd4_op_u {TYPE_1__ secinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  exp_put (scalar_t__) ; 

__attribute__((used)) static void
nfsd4_secinfo_release(union nfsd4_op_u *u)
{
	if (u->secinfo.si_exp)
		exp_put(u->secinfo.si_exp);
}