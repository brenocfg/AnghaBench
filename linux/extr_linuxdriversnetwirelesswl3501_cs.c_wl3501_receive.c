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
typedef  int u8 ;
typedef  int u16 ;
struct wl3501_rx_hdr {int dummy; } ;
struct wl3501_card {int start_seg; } ;
typedef  int /*<<< orphan*/  next_addr1 ;
typedef  int /*<<< orphan*/  next_addr ;

/* Variables and functions */
 int WL3501_BLKSZ ; 
 int /*<<< orphan*/  wl3501_get_from_wla (struct wl3501_card*,int,int*,int) ; 

__attribute__((used)) static u16 wl3501_receive(struct wl3501_card *this, u8 *bf, u16 size)
{
	u16 next_addr, next_addr1;
	u8 *data = bf + 12;

	size -= 12;
	wl3501_get_from_wla(this, this->start_seg + 2,
			    &next_addr, sizeof(next_addr));
	if (size > WL3501_BLKSZ - sizeof(struct wl3501_rx_hdr)) {
		wl3501_get_from_wla(this,
				    this->start_seg +
					sizeof(struct wl3501_rx_hdr), data,
				    WL3501_BLKSZ -
					sizeof(struct wl3501_rx_hdr));
		size -= WL3501_BLKSZ - sizeof(struct wl3501_rx_hdr);
		data += WL3501_BLKSZ - sizeof(struct wl3501_rx_hdr);
	} else {
		wl3501_get_from_wla(this,
				    this->start_seg +
					sizeof(struct wl3501_rx_hdr),
				    data, size);
		size = 0;
	}
	while (size > 0) {
		if (size > WL3501_BLKSZ - 5) {
			wl3501_get_from_wla(this, next_addr + 5, data,
					    WL3501_BLKSZ - 5);
			size -= WL3501_BLKSZ - 5;
			data += WL3501_BLKSZ - 5;
			wl3501_get_from_wla(this, next_addr + 2, &next_addr1,
					    sizeof(next_addr1));
			next_addr = next_addr1;
		} else {
			wl3501_get_from_wla(this, next_addr + 5, data, size);
			size = 0;
		}
	}
	return 0;
}