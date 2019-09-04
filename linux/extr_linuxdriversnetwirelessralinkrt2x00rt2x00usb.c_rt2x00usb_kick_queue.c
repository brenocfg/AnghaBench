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
struct data_queue {int qid; } ;

/* Variables and functions */
#define  QID_AC_BE 132 
#define  QID_AC_BK 131 
#define  QID_AC_VI 130 
#define  QID_AC_VO 129 
#define  QID_RX 128 
 int /*<<< orphan*/  Q_INDEX ; 
 int /*<<< orphan*/  Q_INDEX_DONE ; 
 int /*<<< orphan*/  rt2x00queue_empty (struct data_queue*) ; 
 int /*<<< orphan*/  rt2x00queue_for_each_entry (struct data_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00queue_full (struct data_queue*) ; 
 int /*<<< orphan*/  rt2x00usb_kick_rx_entry ; 
 int /*<<< orphan*/  rt2x00usb_kick_tx_entry ; 

void rt2x00usb_kick_queue(struct data_queue *queue)
{
	switch (queue->qid) {
	case QID_AC_VO:
	case QID_AC_VI:
	case QID_AC_BE:
	case QID_AC_BK:
		if (!rt2x00queue_empty(queue))
			rt2x00queue_for_each_entry(queue,
						   Q_INDEX_DONE,
						   Q_INDEX,
						   NULL,
						   rt2x00usb_kick_tx_entry);
		break;
	case QID_RX:
		if (!rt2x00queue_full(queue))
			rt2x00queue_for_each_entry(queue,
						   Q_INDEX,
						   Q_INDEX_DONE,
						   NULL,
						   rt2x00usb_kick_rx_entry);
		break;
	default:
		break;
	}
}