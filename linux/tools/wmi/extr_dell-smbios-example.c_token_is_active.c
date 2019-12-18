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
struct TYPE_2__ {scalar_t__* output; scalar_t__* input; int /*<<< orphan*/  cmd_select; int /*<<< orphan*/  cmd_class; } ;
struct dell_wmi_smbios_buffer {TYPE_1__ std; } ;
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_TOKEN_READ ; 
 int /*<<< orphan*/  SELECT_TOKEN_STD ; 
 int run_wmi_smbios_cmd (struct dell_wmi_smbios_buffer*) ; 

__attribute__((used)) static int token_is_active(__u16 *location, __u16 *cmpvalue,
			   struct dell_wmi_smbios_buffer *buffer)
{
	int ret;

	buffer->std.cmd_class = CLASS_TOKEN_READ;
	buffer->std.cmd_select = SELECT_TOKEN_STD;
	buffer->std.input[0] = *location;
	ret = run_wmi_smbios_cmd(buffer);
	if (ret != 0 || buffer->std.output[0] != 0)
		return ret;
	ret = (buffer->std.output[1] == *cmpvalue);
	return ret;
}