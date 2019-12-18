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
 int /*<<< orphan*/  exec_other_validate_cap (char*,int,int,int,int) ; 

__attribute__((used)) static void exec_validate_cap(bool eff, bool perm, bool inh, bool ambient)
{
	exec_other_validate_cap("./validate_cap", eff, perm, inh, ambient);
}