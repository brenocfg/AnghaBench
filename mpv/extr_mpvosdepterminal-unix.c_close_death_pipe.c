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
 int /*<<< orphan*/  close (int) ; 
 int* death_pipe ; 

__attribute__((used)) static void close_death_pipe(void)
{
    for (int n = 0; n < 2; n++) {
        if (death_pipe[n] >= 0)
            close(death_pipe[n]);
        death_pipe[n] = -1;
    }
}