#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TransactionState ;
struct TYPE_3__ {int /*<<< orphan*/  curTransactionOwner; } ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentResourceOwner ; 
 TYPE_1__* CurrentTransactionState ; 

__attribute__((used)) static void
AtSubAbort_ResourceOwner(void)
{
	TransactionState s = CurrentTransactionState;

	/* Make sure we have a valid ResourceOwner */
	CurrentResourceOwner = s->curTransactionOwner;
}