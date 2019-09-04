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
typedef  scalar_t__ u32 ;
struct vmbus_channel {int /*<<< orphan*/  outbound; } ;

/* Variables and functions */
 scalar_t__ HVS_PKT_LEN (int) ; 
 scalar_t__ hv_get_bytes_to_write (int /*<<< orphan*/ *) ; 
 size_t round_down (size_t,int) ; 

__attribute__((used)) static size_t hvs_channel_writable_bytes(struct vmbus_channel *chan)
{
	u32 writeable = hv_get_bytes_to_write(&chan->outbound);
	size_t ret;

	/* The ringbuffer mustn't be 100% full, and we should reserve a
	 * zero-length-payload packet for the FIN: see hv_ringbuffer_write()
	 * and hvs_shutdown().
	 */
	if (writeable <= HVS_PKT_LEN(1) + HVS_PKT_LEN(0))
		return 0;

	ret = writeable - HVS_PKT_LEN(1) - HVS_PKT_LEN(0);

	return round_down(ret, 8);
}