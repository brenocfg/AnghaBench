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
 scalar_t__ LSCRIU_need_checkpoint () ; 
 int /*<<< orphan*/  LSCRIU_try_checkpoint (int*) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  lscriu_dbg (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void LSCRIU_on_timer(int *forked_pid)
{
    lscriu_dbg("LSCRIU (%d): LSCRIU_on_timer\n", getpid());
    if (LSCRIU_need_checkpoint()) {
        LSCRIU_try_checkpoint(forked_pid);
    }
}