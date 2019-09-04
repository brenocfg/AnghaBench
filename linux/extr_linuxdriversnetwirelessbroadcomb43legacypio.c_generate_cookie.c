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
typedef  int u16 ;
struct b43legacy_pioqueue {int mmio_base; } ;
struct b43legacy_pio_txpacket {int dummy; } ;

/* Variables and functions */
#define  B43legacy_MMIO_PIO1_BASE 131 
#define  B43legacy_MMIO_PIO2_BASE 130 
#define  B43legacy_MMIO_PIO3_BASE 129 
#define  B43legacy_MMIO_PIO4_BASE 128 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int pio_txpacket_getindex (struct b43legacy_pio_txpacket*) ; 

__attribute__((used)) static u16 generate_cookie(struct b43legacy_pioqueue *queue,
			   struct b43legacy_pio_txpacket *packet)
{
	u16 cookie = 0x0000;
	int packetindex;

	/* We use the upper 4 bits for the PIO
	 * controller ID and the lower 12 bits
	 * for the packet index (in the cache).
	 */
	switch (queue->mmio_base) {
	case B43legacy_MMIO_PIO1_BASE:
		break;
	case B43legacy_MMIO_PIO2_BASE:
		cookie = 0x1000;
		break;
	case B43legacy_MMIO_PIO3_BASE:
		cookie = 0x2000;
		break;
	case B43legacy_MMIO_PIO4_BASE:
		cookie = 0x3000;
		break;
	default:
		B43legacy_WARN_ON(1);
	}
	packetindex = pio_txpacket_getindex(packet);
	B43legacy_WARN_ON(!(((u16)packetindex & 0xF000) == 0x0000));
	cookie |= (u16)packetindex;

	return cookie;
}