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
 int /*<<< orphan*/  fast_breakcheck () ; 
 int /*<<< orphan*/  reg_getline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reginput ; 
 int /*<<< orphan*/  regline ; 
 int /*<<< orphan*/  reglnum ; 

__attribute__((used)) static void
reg_nextline()
{
    regline = reg_getline(++reglnum);
    reginput = regline;
    fast_breakcheck();
}