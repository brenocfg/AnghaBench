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
 int /*<<< orphan*/  STATEMENT_TIMEOUT ; 
 int /*<<< orphan*/  disable_timeout (int /*<<< orphan*/ ,int) ; 
 scalar_t__ get_timeout_active (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
disable_statement_timeout(void)
{
	if (get_timeout_active(STATEMENT_TIMEOUT))
		disable_timeout(STATEMENT_TIMEOUT, false);
}