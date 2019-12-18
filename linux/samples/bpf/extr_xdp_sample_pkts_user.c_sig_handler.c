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
 int /*<<< orphan*/  do_detach (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_idx ; 
 int /*<<< orphan*/  if_name ; 
 int /*<<< orphan*/  pb ; 
 int /*<<< orphan*/  perf_buffer__free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sig_handler(int signo)
{
	do_detach(if_idx, if_name);
	perf_buffer__free(pb);
	exit(0);
}