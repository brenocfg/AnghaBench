#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ rmem; } ;
typedef  TYPE_1__ ray_dev_t ;
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 int RX_BUFF_END ; 
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static int copy_from_rx_buff(ray_dev_t *local, UCHAR *dest, int pkt_addr,
			     int length)
{
	int wrap_bytes = (pkt_addr + length) - (RX_BUFF_END + 1);
	if (wrap_bytes <= 0) {
		memcpy_fromio(dest, local->rmem + pkt_addr, length);
	} else { /* Packet wrapped in circular buffer */

		memcpy_fromio(dest, local->rmem + pkt_addr,
			      length - wrap_bytes);
		memcpy_fromio(dest + length - wrap_bytes, local->rmem,
			      wrap_bytes);
	}
	return length;
}