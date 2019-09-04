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
 int /*<<< orphan*/  python_scripting_unsupported_ops ; 
 int /*<<< orphan*/  register_python_scripting (int /*<<< orphan*/ *) ; 

void setup_python_scripting(void)
{
	register_python_scripting(&python_scripting_unsupported_ops);
}