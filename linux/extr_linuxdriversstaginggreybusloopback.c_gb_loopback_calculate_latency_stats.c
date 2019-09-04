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
struct gb_loopback {int /*<<< orphan*/  gbphy_latency_ts; int /*<<< orphan*/  gbphy_firmware_latency; int /*<<< orphan*/  apbridge_latency_ts; int /*<<< orphan*/  apbridge_unipro_latency; int /*<<< orphan*/  kfifo_lat; int /*<<< orphan*/  latency; int /*<<< orphan*/  elapsed_nsecs; } ;
typedef  int /*<<< orphan*/  lat ;

/* Variables and functions */
 int /*<<< orphan*/  gb_loopback_nsec_to_usec_latency (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_loopback_update_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_in (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static void gb_loopback_calculate_latency_stats(struct gb_loopback *gb)
{
	u32 lat;

	/* Express latency in terms of microseconds */
	lat = gb_loopback_nsec_to_usec_latency(gb->elapsed_nsecs);

	/* Log latency stastic */
	gb_loopback_update_stats(&gb->latency, lat);

	/* Raw latency log on a per thread basis */
	kfifo_in(&gb->kfifo_lat, (unsigned char *)&lat, sizeof(lat));

	/* Log the firmware supplied latency values */
	gb_loopback_update_stats(&gb->apbridge_unipro_latency,
				 gb->apbridge_latency_ts);
	gb_loopback_update_stats(&gb->gbphy_firmware_latency,
				 gb->gbphy_latency_ts);
}