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
struct dell_wmi_smbios_buffer {TYPE_1__ std; scalar_t__ length; } ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  CAPSULE_DIS_TOKEN ; 
 int /*<<< orphan*/  CAPSULE_EN_TOKEN ; 
 int /*<<< orphan*/  CLASS_FLASH_INTERFACE ; 
 int ENOMEM ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  SELECT_FLASH_INTERFACE ; 
 scalar_t__ activate_token (struct dell_wmi_smbios_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct dell_wmi_smbios_buffer*) ; 
 struct dell_wmi_smbios_buffer* malloc (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int query_buffer_size (scalar_t__*) ; 
 int query_token (int /*<<< orphan*/ ,struct dell_wmi_smbios_buffer*) ; 
 int run_wmi_smbios_cmd (struct dell_wmi_smbios_buffer*) ; 
 int /*<<< orphan*/  show_buffer (struct dell_wmi_smbios_buffer*) ; 

int main(void)
{
	struct dell_wmi_smbios_buffer *buffer;
	int ret;
	__u64 value = 0;

	ret = query_buffer_size(&value);
	if (ret == EXIT_FAILURE || !value) {
		printf("Unable to read buffer size\n");
		goto out;
	}
	printf("Detected required buffer size %lld\n", value);

	buffer = malloc(value);
	if (buffer == NULL) {
		printf("failed to alloc memory for ioctl\n");
		ret = -ENOMEM;
		goto out;
	}
	buffer->length = value;

	/* simple SMBIOS call for looking up TPM info */
	buffer->std.cmd_class = CLASS_FLASH_INTERFACE;
	buffer->std.cmd_select = SELECT_FLASH_INTERFACE;
	buffer->std.input[0] = 2;
	ret = run_wmi_smbios_cmd(buffer);
	if (ret) {
		printf("smbios ioctl failed: %d\n", ret);
		ret = EXIT_FAILURE;
		goto out;
	}
	show_buffer(buffer);

	/* query some tokens */
	ret = query_token(CAPSULE_EN_TOKEN, buffer);
	printf("UEFI Capsule enabled token is: %d\n", ret);
	ret = query_token(CAPSULE_DIS_TOKEN, buffer);
	printf("UEFI Capsule disabled token is: %d\n", ret);

	/* activate UEFI capsule token if disabled */
	if (ret) {
		printf("Enabling UEFI capsule token");
		if (activate_token(buffer, CAPSULE_EN_TOKEN)) {
			printf("activate failed\n");
			ret = -1;
			goto out;
		}
	}
	ret = EXIT_SUCCESS;
out:
	free(buffer);
	return ret;
}