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
struct rt2x00_dev {int dummy; } ;
struct queue_entry_priv_usb {int dummy; } ;
struct data_queue {int qid; int limit; unsigned short winfo_size; int priv_size; void* desc_size; void* data_size; struct rt2x00_dev* rt2x00dev; } ;

/* Variables and functions */
 void* AGGREGATION_SIZE ; 
 int /*<<< orphan*/  BUG () ; 
 void* MGMT_FRAME_SIZE ; 
#define  QID_AC_BE 134 
#define  QID_AC_BK 133 
#define  QID_AC_VI 132 
#define  QID_AC_VO 131 
#define  QID_ATIM 130 
#define  QID_BEACON 129 
#define  QID_RX 128 
 void* RXINFO_DESC_SIZE ; 
 void* TXINFO_DESC_SIZE ; 
 int /*<<< orphan*/  rt2800_get_txwi_rxwi_size (struct rt2x00_dev*,unsigned short*,unsigned short*) ; 

__attribute__((used)) static void rt2800usb_queue_init(struct data_queue *queue)
{
	struct rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	unsigned short txwi_size, rxwi_size;

	rt2800_get_txwi_rxwi_size(rt2x00dev, &txwi_size, &rxwi_size);

	switch (queue->qid) {
	case QID_RX:
		queue->limit = 128;
		queue->data_size = AGGREGATION_SIZE;
		queue->desc_size = RXINFO_DESC_SIZE;
		queue->winfo_size = rxwi_size;
		queue->priv_size = sizeof(struct queue_entry_priv_usb);
		break;

	case QID_AC_VO:
	case QID_AC_VI:
	case QID_AC_BE:
	case QID_AC_BK:
		queue->limit = 16;
		queue->data_size = AGGREGATION_SIZE;
		queue->desc_size = TXINFO_DESC_SIZE;
		queue->winfo_size = txwi_size;
		queue->priv_size = sizeof(struct queue_entry_priv_usb);
		break;

	case QID_BEACON:
		queue->limit = 8;
		queue->data_size = MGMT_FRAME_SIZE;
		queue->desc_size = TXINFO_DESC_SIZE;
		queue->winfo_size = txwi_size;
		queue->priv_size = sizeof(struct queue_entry_priv_usb);
		break;

	case QID_ATIM:
		/* fallthrough */
	default:
		BUG();
		break;
	}
}