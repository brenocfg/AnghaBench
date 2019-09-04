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
typedef  int /*<<< orphan*/  u8 ;
struct wmi_block {int dummy; } ;
struct acpi_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  __query_block (struct wmi_block*,int /*<<< orphan*/ ,struct acpi_buffer*) ; 
 int /*<<< orphan*/  find_guid (char const*,struct wmi_block**) ; 

acpi_status wmi_query_block(const char *guid_string, u8 instance,
			    struct acpi_buffer *out)
{
	struct wmi_block *wblock;

	if (!guid_string)
		return AE_BAD_PARAMETER;

	if (!find_guid(guid_string, &wblock))
		return AE_ERROR;

	return __query_block(wblock, instance, out);
}