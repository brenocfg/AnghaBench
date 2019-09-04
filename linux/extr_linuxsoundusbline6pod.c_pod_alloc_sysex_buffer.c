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
struct usb_line6_pod {int /*<<< orphan*/  line6; } ;

/* Variables and functions */
 int /*<<< orphan*/  POD_SYSEX_CODE ; 
 char* line6_alloc_sysex_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static char *pod_alloc_sysex_buffer(struct usb_line6_pod *pod, int code,
				    int size)
{
	return line6_alloc_sysex_buffer(&pod->line6, POD_SYSEX_CODE, code,
					size);
}