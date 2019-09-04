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
typedef  int /*<<< orphan*/  u8 ;
struct gsm_mux {int mtu; int /*<<< orphan*/  ftype; } ;
struct gsm_msg {int /*<<< orphan*/ * data; } ;
struct gsm_dlci {int adaption; int /*<<< orphan*/  lock; int /*<<< orphan*/  fifo; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __gsm_data_queue (struct gsm_dlci*,struct gsm_msg*) ; 
 struct gsm_msg* gsm_data_alloc (struct gsm_mux*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsm_encode_modem (struct gsm_dlci*) ; 
 int kfifo_len (int /*<<< orphan*/ ) ; 
 int kfifo_out_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gsm_dlci_data_output(struct gsm_mux *gsm, struct gsm_dlci *dlci)
{
	struct gsm_msg *msg;
	u8 *dp;
	int len, total_size, size;
	int h = dlci->adaption - 1;

	total_size = 0;
	while (1) {
		len = kfifo_len(dlci->fifo);
		if (len == 0)
			return total_size;

		/* MTU/MRU count only the data bits */
		if (len > gsm->mtu)
			len = gsm->mtu;

		size = len + h;

		msg = gsm_data_alloc(gsm, dlci->addr, size, gsm->ftype);
		/* FIXME: need a timer or something to kick this so it can't
		   get stuck with no work outstanding and no buffer free */
		if (msg == NULL)
			return -ENOMEM;
		dp = msg->data;
		switch (dlci->adaption) {
		case 1:	/* Unstructured */
			break;
		case 2:	/* Unstructed with modem bits.
		Always one byte as we never send inline break data */
			*dp++ = gsm_encode_modem(dlci);
			break;
		}
		WARN_ON(kfifo_out_locked(dlci->fifo, dp , len, &dlci->lock) != len);
		__gsm_data_queue(dlci, msg);
		total_size += size;
	}
	/* Bytes of data we used up */
	return total_size;
}