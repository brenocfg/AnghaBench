#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int cmd_class; int cmd_select; int* input; int* output; } ;
struct dell_wmi_smbios_buffer {TYPE_1__ std; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static void show_buffer(struct dell_wmi_smbios_buffer *buffer)
{
	printf("Call: %x/%x [%x,%x,%x,%x]\nResults: [%8x,%8x,%8x,%8x]\n",
	buffer->std.cmd_class, buffer->std.cmd_select,
	buffer->std.input[0], buffer->std.input[1],
	buffer->std.input[2], buffer->std.input[3],
	buffer->std.output[0], buffer->std.output[1],
	buffer->std.output[2], buffer->std.output[3]);
}