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
typedef  int /*<<< orphan*/  u32 ;
struct ucsi_acpi {int /*<<< orphan*/  ucsi; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ucsi_notify (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ucsi_acpi_notify(acpi_handle handle, u32 event, void *data)
{
	struct ucsi_acpi *ua = data;

	ucsi_notify(ua->ucsi);
}