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
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  kuhl_m_busylight_devices ; 
 int /*<<< orphan*/  kull_m_busylight_devices_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_busylight_clean()
{
	kull_m_busylight_devices_free(kuhl_m_busylight_devices, TRUE);
	return STATUS_SUCCESS;
}