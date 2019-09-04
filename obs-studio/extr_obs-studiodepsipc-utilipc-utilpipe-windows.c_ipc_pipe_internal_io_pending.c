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
 scalar_t__ ERROR_IO_PENDING ; 
 scalar_t__ GetLastError () ; 

__attribute__((used)) static inline bool ipc_pipe_internal_io_pending(void)
{
	return GetLastError() == ERROR_IO_PENDING;
}