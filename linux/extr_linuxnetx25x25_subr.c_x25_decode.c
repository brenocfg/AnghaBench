#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct x25_sock {TYPE_1__* neighbour; } ;
struct sock {int dummy; } ;
struct sk_buff {unsigned char* data; } ;
struct TYPE_2__ {scalar_t__ extended; } ;

/* Variables and functions */
#define  X25_CALL_ACCEPTED 140 
#define  X25_CALL_REQUEST 139 
#define  X25_CLEAR_CONFIRMATION 138 
#define  X25_CLEAR_REQUEST 137 
 unsigned char X25_DATA ; 
#define  X25_DIAGNOSTIC 136 
 unsigned char X25_D_BIT ; 
 int /*<<< orphan*/  X25_EXT_MIN_LEN ; 
 unsigned char X25_EXT_M_BIT ; 
 int X25_ILLEGAL ; 
#define  X25_INTERRUPT 135 
#define  X25_INTERRUPT_CONFIRMATION 134 
 unsigned char X25_Q_BIT ; 
#define  X25_REGISTRATION_CONFIRMATION 133 
#define  X25_REGISTRATION_REQUEST 132 
 unsigned char X25_REJ ; 
#define  X25_RESET_CONFIRMATION 131 
#define  X25_RESET_REQUEST 130 
#define  X25_RESTART_CONFIRMATION 129 
#define  X25_RESTART_REQUEST 128 
 unsigned char X25_RNR ; 
 unsigned char X25_RR ; 
 int /*<<< orphan*/  X25_STD_MIN_LEN ; 
 unsigned char X25_STD_M_BIT ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned char*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct x25_sock* x25_sk (struct sock*) ; 

int x25_decode(struct sock *sk, struct sk_buff *skb, int *ns, int *nr, int *q,
	       int *d, int *m)
{
	struct x25_sock *x25 = x25_sk(sk);
	unsigned char *frame;

	if (!pskb_may_pull(skb, X25_STD_MIN_LEN))
		return X25_ILLEGAL;
	frame = skb->data;

	*ns = *nr = *q = *d = *m = 0;

	switch (frame[2]) {
	case X25_CALL_REQUEST:
	case X25_CALL_ACCEPTED:
	case X25_CLEAR_REQUEST:
	case X25_CLEAR_CONFIRMATION:
	case X25_INTERRUPT:
	case X25_INTERRUPT_CONFIRMATION:
	case X25_RESET_REQUEST:
	case X25_RESET_CONFIRMATION:
	case X25_RESTART_REQUEST:
	case X25_RESTART_CONFIRMATION:
	case X25_REGISTRATION_REQUEST:
	case X25_REGISTRATION_CONFIRMATION:
	case X25_DIAGNOSTIC:
		return frame[2];
	}

	if (x25->neighbour->extended) {
		if (frame[2] == X25_RR  ||
		    frame[2] == X25_RNR ||
		    frame[2] == X25_REJ) {
			if (!pskb_may_pull(skb, X25_EXT_MIN_LEN))
				return X25_ILLEGAL;
			frame = skb->data;

			*nr = (frame[3] >> 1) & 0x7F;
			return frame[2];
		}
	} else {
		if ((frame[2] & 0x1F) == X25_RR  ||
		    (frame[2] & 0x1F) == X25_RNR ||
		    (frame[2] & 0x1F) == X25_REJ) {
			*nr = (frame[2] >> 5) & 0x07;
			return frame[2] & 0x1F;
		}
	}

	if (x25->neighbour->extended) {
		if ((frame[2] & 0x01) == X25_DATA) {
			if (!pskb_may_pull(skb, X25_EXT_MIN_LEN))
				return X25_ILLEGAL;
			frame = skb->data;

			*q  = (frame[0] & X25_Q_BIT) == X25_Q_BIT;
			*d  = (frame[0] & X25_D_BIT) == X25_D_BIT;
			*m  = (frame[3] & X25_EXT_M_BIT) == X25_EXT_M_BIT;
			*nr = (frame[3] >> 1) & 0x7F;
			*ns = (frame[2] >> 1) & 0x7F;
			return X25_DATA;
		}
	} else {
		if ((frame[2] & 0x01) == X25_DATA) {
			*q  = (frame[0] & X25_Q_BIT) == X25_Q_BIT;
			*d  = (frame[0] & X25_D_BIT) == X25_D_BIT;
			*m  = (frame[2] & X25_STD_M_BIT) == X25_STD_M_BIT;
			*nr = (frame[2] >> 5) & 0x07;
			*ns = (frame[2] >> 1) & 0x07;
			return X25_DATA;
		}
	}

	pr_debug("invalid PLP frame %3ph\n", frame);

	return X25_ILLEGAL;
}