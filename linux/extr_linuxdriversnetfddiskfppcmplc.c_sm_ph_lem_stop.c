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
struct s_smc {TYPE_1__* y; } ;
struct lem_counter {scalar_t__ lem_on; } ;
struct TYPE_2__ {struct lem_counter lem; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLC (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PL_INTR_MASK ; 
 int /*<<< orphan*/  PL_LE_CTR ; 

__attribute__((used)) static void sm_ph_lem_stop(struct s_smc *smc, int np)
{
	struct lem_counter *lem = &smc->y[np].lem ;

	lem->lem_on = 0 ;
	CLEAR(PLC(np,PL_INTR_MASK),PL_LE_CTR) ;
}