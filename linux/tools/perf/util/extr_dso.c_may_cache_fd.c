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
typedef  scalar_t__ rlim_t ;

/* Variables and functions */
 scalar_t__ RLIM_INFINITY ; 
 scalar_t__ dso__data_open_cnt ; 
 scalar_t__ fd_limit ; 
 scalar_t__ get_fd_limit () ; 

__attribute__((used)) static bool may_cache_fd(void)
{
	if (!fd_limit)
		fd_limit = get_fd_limit();

	if (fd_limit == RLIM_INFINITY)
		return true;

	return fd_limit > (rlim_t) dso__data_open_cnt;
}