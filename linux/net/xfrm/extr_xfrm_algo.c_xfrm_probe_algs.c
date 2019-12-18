#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int available; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int available; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int available; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 int aalg_entries () ; 
 TYPE_3__* aalg_list ; 
 int calg_entries () ; 
 TYPE_2__* calg_list ; 
 int crypto_has_ahash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_has_comp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_has_skcipher (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ealg_entries () ; 
 TYPE_1__* ealg_list ; 
 int /*<<< orphan*/  in_softirq () ; 

void xfrm_probe_algs(void)
{
	int i, status;

	BUG_ON(in_softirq());

	for (i = 0; i < aalg_entries(); i++) {
		status = crypto_has_ahash(aalg_list[i].name, 0, 0);
		if (aalg_list[i].available != status)
			aalg_list[i].available = status;
	}

	for (i = 0; i < ealg_entries(); i++) {
		status = crypto_has_skcipher(ealg_list[i].name, 0, 0);
		if (ealg_list[i].available != status)
			ealg_list[i].available = status;
	}

	for (i = 0; i < calg_entries(); i++) {
		status = crypto_has_comp(calg_list[i].name, 0,
					 CRYPTO_ALG_ASYNC);
		if (calg_list[i].available != status)
			calg_list[i].available = status;
	}
}