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
struct cm_dev {void** rx_buf; int /*<<< orphan*/  rx_slots; int /*<<< orphan*/  mport; } ;

/* Variables and functions */
 int RIOCM_RX_RING_SIZE ; 
 int /*<<< orphan*/  cmbox ; 
 void* rio_get_inb_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  riocm_warn (char*,void*) ; 

__attribute__((used)) static void *riocm_rx_get_msg(struct cm_dev *cm)
{
	void *msg;
	int i;

	msg = rio_get_inb_message(cm->mport, cmbox);
	if (msg) {
		for (i = 0; i < RIOCM_RX_RING_SIZE; i++) {
			if (cm->rx_buf[i] == msg) {
				cm->rx_buf[i] = NULL;
				cm->rx_slots++;
				break;
			}
		}

		if (i == RIOCM_RX_RING_SIZE)
			riocm_warn("no record for buffer 0x%p", msg);
	}

	return msg;
}