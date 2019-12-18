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

/* Variables and functions */
 int /*<<< orphan*/  CurrentTransactionState ; 
 scalar_t__ DEBUG5 ; 
 int /*<<< orphan*/  ShowTransactionStateRec (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ client_min_messages ; 
 scalar_t__ log_min_messages ; 

__attribute__((used)) static void
ShowTransactionState(const char *str)
{
	/* skip work if message will definitely not be printed */
	if (log_min_messages <= DEBUG5 || client_min_messages <= DEBUG5)
		ShowTransactionStateRec(str, CurrentTransactionState);
}