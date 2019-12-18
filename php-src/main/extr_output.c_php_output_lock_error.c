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
 int /*<<< orphan*/  E_ERROR ; 
 scalar_t__ OG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  active ; 
 int /*<<< orphan*/  php_error_docref (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  php_output_deactivate () ; 
 int /*<<< orphan*/  running ; 

__attribute__((used)) static inline int php_output_lock_error(int op)
{
	/* if there's no ob active, ob has been stopped */
	if (op && OG(active) && OG(running)) {
		/* fatal error */
		php_output_deactivate();
		php_error_docref("ref.outcontrol", E_ERROR, "Cannot use output buffering in output buffering display handlers");
		return 1;
	}
	return 0;
}