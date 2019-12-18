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
 int SIGTERM ; 
 int SIGUSR1 ; 
 int in_shutdown ; 

__attribute__((used)) static void fcgi_signal_handler(int signo)
{
	if (signo == SIGUSR1 || signo == SIGTERM) {
		in_shutdown = 1;
	}
}