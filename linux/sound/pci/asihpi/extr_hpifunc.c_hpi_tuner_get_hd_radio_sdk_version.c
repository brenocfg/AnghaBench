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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_TUNER_HDRADIO_SDK_VERSION ; 
 int /*<<< orphan*/  hpi_control_get_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const) ; 

u16 hpi_tuner_get_hd_radio_sdk_version(u32 h_control, char *psz_sdk_version,
	const u32 string_size)
{
	return hpi_control_get_string(h_control,
		HPI_TUNER_HDRADIO_SDK_VERSION, psz_sdk_version, string_size);
}