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
struct TYPE_2__ {int* input; int /*<<< orphan*/  cmd_select; int /*<<< orphan*/  cmd_class; } ;
struct dell_wmi_smbios_buffer {TYPE_1__ std; } ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_TOKEN_WRITE ; 
 int /*<<< orphan*/  SELECT_TOKEN_STD ; 
 int find_token (int,int*,int*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int run_wmi_smbios_cmd (struct dell_wmi_smbios_buffer*) ; 

__attribute__((used)) static int activate_token(struct dell_wmi_smbios_buffer *buffer,
		   __u16 token)
{
	__u16 location;
	__u16 value;
	int ret;

	ret = find_token(token, &location, &value);
	if (ret != 0) {
		printf("unable to find token %04x\n", token);
		return 1;
	}
	buffer->std.cmd_class = CLASS_TOKEN_WRITE;
	buffer->std.cmd_select = SELECT_TOKEN_STD;
	buffer->std.input[0] = location;
	buffer->std.input[1] = 1;
	ret = run_wmi_smbios_cmd(buffer);
	return ret;
}