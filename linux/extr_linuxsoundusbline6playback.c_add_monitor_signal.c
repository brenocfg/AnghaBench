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
struct urb {int transfer_buffer_length; scalar_t__ transfer_buffer; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 short clamp (int,int,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (short) ; 
 short le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_monitor_signal(struct urb *urb_out, unsigned char *signal,
			       int volume, int bytes_per_frame)
{
	if (volume == 0)
		return;		/* zero volume - no change */

	if (bytes_per_frame == 4) {
		__le16 *pi, *po, *buf_end;

		pi = (__le16 *)signal;
		po = (__le16 *)urb_out->transfer_buffer;
		buf_end = po + urb_out->transfer_buffer_length / sizeof(*po);

		for (; po < buf_end; ++pi, ++po) {
			short pov = le16_to_cpu(*po);
			short piv = le16_to_cpu(*pi);
			int val = pov + ((piv * volume) >> 8);
			pov = clamp(val, -0x8000, 0x7fff);
			*po = cpu_to_le16(pov);
		}
	}

	/*
	   We don't need to handle devices with 6 bytes per frame here
	   since they all support hardware monitoring.
	 */
}