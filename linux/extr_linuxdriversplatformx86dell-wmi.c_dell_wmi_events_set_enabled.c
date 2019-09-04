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
struct calling_interface_buffer {int* input; int* output; int /*<<< orphan*/  cmd_select; int /*<<< orphan*/  cmd_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_INFO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SELECT_APP_REGISTRATION ; 
 int dell_smbios_call (struct calling_interface_buffer*) ; 
 int dell_smbios_error (int) ; 
 int /*<<< orphan*/  kfree (struct calling_interface_buffer*) ; 
 struct calling_interface_buffer* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dell_wmi_events_set_enabled(bool enable)
{
	struct calling_interface_buffer *buffer;
	int ret;

	buffer = kzalloc(sizeof(struct calling_interface_buffer), GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;
	buffer->cmd_class = CLASS_INFO;
	buffer->cmd_select = SELECT_APP_REGISTRATION;
	buffer->input[0] = 0x10000;
	buffer->input[1] = 0x51534554;
	buffer->input[3] = enable;
	ret = dell_smbios_call(buffer);
	if (ret == 0)
		ret = buffer->output[0];
	kfree(buffer);

	return dell_smbios_error(ret);
}