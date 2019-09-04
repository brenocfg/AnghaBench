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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct efx_nic {int rx_packet_ts_offset; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 efx_rx_buf_timestamp_minor(struct efx_nic *efx, const u8 *eh)
{
#if defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS)
	return __le32_to_cpup((const __le32 *)(eh + efx->rx_packet_ts_offset));
#else
	const u8 *data = eh + efx->rx_packet_ts_offset;
	return (u32)data[0]       |
	       (u32)data[1] << 8  |
	       (u32)data[2] << 16 |
	       (u32)data[3] << 24;
#endif
}