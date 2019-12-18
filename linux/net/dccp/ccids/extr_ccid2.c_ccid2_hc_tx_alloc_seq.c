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
struct ccid2_seq {struct ccid2_seq* ccid2s_next; struct ccid2_seq* ccid2s_prev; } ;
struct ccid2_hc_tx_sock {int tx_seqbufc; struct ccid2_seq** tx_seqbuf; struct ccid2_seq* tx_seqt; struct ccid2_seq* tx_seqh; } ;

/* Variables and functions */
 int CCID2_SEQBUF_LEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  gfp_any () ; 
 struct ccid2_seq* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccid2_hc_tx_alloc_seq(struct ccid2_hc_tx_sock *hc)
{
	struct ccid2_seq *seqp;
	int i;

	/* check if we have space to preserve the pointer to the buffer */
	if (hc->tx_seqbufc >= (sizeof(hc->tx_seqbuf) /
			       sizeof(struct ccid2_seq *)))
		return -ENOMEM;

	/* allocate buffer and initialize linked list */
	seqp = kmalloc_array(CCID2_SEQBUF_LEN, sizeof(struct ccid2_seq),
			     gfp_any());
	if (seqp == NULL)
		return -ENOMEM;

	for (i = 0; i < (CCID2_SEQBUF_LEN - 1); i++) {
		seqp[i].ccid2s_next = &seqp[i + 1];
		seqp[i + 1].ccid2s_prev = &seqp[i];
	}
	seqp[CCID2_SEQBUF_LEN - 1].ccid2s_next = seqp;
	seqp->ccid2s_prev = &seqp[CCID2_SEQBUF_LEN - 1];

	/* This is the first allocation.  Initiate the head and tail.  */
	if (hc->tx_seqbufc == 0)
		hc->tx_seqh = hc->tx_seqt = seqp;
	else {
		/* link the existing list with the one we just created */
		hc->tx_seqh->ccid2s_next = seqp;
		seqp->ccid2s_prev = hc->tx_seqh;

		hc->tx_seqt->ccid2s_prev = &seqp[CCID2_SEQBUF_LEN - 1];
		seqp[CCID2_SEQBUF_LEN - 1].ccid2s_next = hc->tx_seqt;
	}

	/* store the original pointer to the buffer so we can free it */
	hc->tx_seqbuf[hc->tx_seqbufc] = seqp;
	hc->tx_seqbufc++;

	return 0;
}