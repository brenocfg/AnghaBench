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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  read (int,char*,int) ; 

void mp_flush_wakeup_pipe(int pipe_end)
{
#ifndef __MINGW32__
    char buf[100];
    (void)read(pipe_end, buf, sizeof(buf));
#endif
}