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
struct smi_cmd {int ecx; int /*<<< orphan*/  ebx; int /*<<< orphan*/  command_code; int /*<<< orphan*/  command_address; int /*<<< orphan*/  magic; } ;
struct calling_interface_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMI_CMD_MAGIC ; 
 struct calling_interface_buffer* buffer ; 
 int /*<<< orphan*/  da_command_address ; 
 int /*<<< orphan*/  da_command_code ; 
 int /*<<< orphan*/  dcdbas_smi_request (struct smi_cmd*) ; 
 int /*<<< orphan*/  memcpy (struct calling_interface_buffer*,struct calling_interface_buffer*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smm_mutex ; 
 int /*<<< orphan*/  virt_to_phys (struct calling_interface_buffer*) ; 

__attribute__((used)) static int dell_smbios_smm_call(struct calling_interface_buffer *input)
{
	struct smi_cmd command;
	size_t size;

	size = sizeof(struct calling_interface_buffer);
	command.magic = SMI_CMD_MAGIC;
	command.command_address = da_command_address;
	command.command_code = da_command_code;
	command.ebx = virt_to_phys(buffer);
	command.ecx = 0x42534931;

	mutex_lock(&smm_mutex);
	memcpy(buffer, input, size);
	dcdbas_smi_request(&command);
	memcpy(input, buffer, size);
	mutex_unlock(&smm_mutex);
	return 0;
}