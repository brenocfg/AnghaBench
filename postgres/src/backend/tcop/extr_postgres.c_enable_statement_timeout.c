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
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATEMENT_TIMEOUT ; 
 scalar_t__ StatementTimeout ; 
 int /*<<< orphan*/  disable_timeout (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  enable_timeout_after (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ get_timeout_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xact_started ; 

__attribute__((used)) static void
enable_statement_timeout(void)
{
	/* must be within an xact */
	Assert(xact_started);

	if (StatementTimeout > 0)
	{
		if (!get_timeout_active(STATEMENT_TIMEOUT))
			enable_timeout_after(STATEMENT_TIMEOUT, StatementTimeout);
	}
	else
	{
		if (get_timeout_active(STATEMENT_TIMEOUT))
			disable_timeout(STATEMENT_TIMEOUT, false);
	}
}