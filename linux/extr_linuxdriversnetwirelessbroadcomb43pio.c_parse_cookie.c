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
struct b43_pio {struct b43_pio_txqueue* tx_queue_mcast; struct b43_pio_txqueue* tx_queue_AC_VO; struct b43_pio_txqueue* tx_queue_AC_VI; struct b43_pio_txqueue* tx_queue_AC_BE; struct b43_pio_txqueue* tx_queue_AC_BK; } ;
struct b43_wldev {struct b43_pio pio; } ;
struct b43_pio_txqueue {struct b43_pio_txpacket* packets; } ;
struct b43_pio_txpacket {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct b43_pio_txpacket*) ; 
 scalar_t__ B43_WARN_ON (int) ; 

__attribute__((used)) static
struct b43_pio_txqueue *parse_cookie(struct b43_wldev *dev,
				     u16 cookie,
				      struct b43_pio_txpacket **pack)
{
	struct b43_pio *pio = &dev->pio;
	struct b43_pio_txqueue *q = NULL;
	unsigned int pack_index;

	switch (cookie & 0xF000) {
	case 0x1000:
		q = pio->tx_queue_AC_BK;
		break;
	case 0x2000:
		q = pio->tx_queue_AC_BE;
		break;
	case 0x3000:
		q = pio->tx_queue_AC_VI;
		break;
	case 0x4000:
		q = pio->tx_queue_AC_VO;
		break;
	case 0x5000:
		q = pio->tx_queue_mcast;
		break;
	}
	if (B43_WARN_ON(!q))
		return NULL;
	pack_index = (cookie & 0x0FFF);
	if (B43_WARN_ON(pack_index >= ARRAY_SIZE(q->packets)))
		return NULL;
	*pack = &q->packets[pack_index];

	return q;
}