#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct efx_ptp_data {TYPE_1__ (* nic_to_kernel_time ) (int,int,int /*<<< orphan*/ ) ;} ;
struct efx_nic {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int last_sync_timestamp_major (struct efx_nic*) ; 
 TYPE_1__ stub1 (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ktime_t
efx_ptp_mac_nic_to_ktime_correction(struct efx_nic *efx,
				    struct efx_ptp_data *ptp,
				    u32 nic_major, u32 nic_minor,
				    s32 correction)
{
	ktime_t kt = { 0 };

	if (!(nic_major & 0x80000000)) {
		WARN_ON_ONCE(nic_major >> 16);
		/* Use the top bits from the latest sync event. */
		nic_major &= 0xffff;
		nic_major |= (last_sync_timestamp_major(efx) & 0xffff0000);

		kt = ptp->nic_to_kernel_time(nic_major, nic_minor,
					     correction);
	}
	return kt;
}