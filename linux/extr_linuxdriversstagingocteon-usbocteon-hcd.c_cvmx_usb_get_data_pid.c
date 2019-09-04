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
struct cvmx_usb_pipe {scalar_t__ pid_toggle; } ;

/* Variables and functions */

__attribute__((used)) static inline int cvmx_usb_get_data_pid(struct cvmx_usb_pipe *pipe)
{
	if (pipe->pid_toggle)
		return 2; /* Data1 */
	return 0; /* Data0 */
}