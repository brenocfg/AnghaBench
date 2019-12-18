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
struct sk_buff {unsigned char* data; } ;

/* Variables and functions */
#define  ROSE_CALL_ACCEPTED 133 
#define  ROSE_CALL_REQUEST 132 
#define  ROSE_CLEAR_CONFIRMATION 131 
#define  ROSE_CLEAR_REQUEST 130 
 unsigned char ROSE_DATA ; 
 unsigned char ROSE_D_BIT ; 
 int ROSE_ILLEGAL ; 
 unsigned char ROSE_M_BIT ; 
 unsigned char ROSE_Q_BIT ; 
#define  ROSE_RESET_CONFIRMATION 129 
#define  ROSE_RESET_REQUEST 128 
 unsigned char ROSE_RNR ; 
 unsigned char ROSE_RR ; 

int rose_decode(struct sk_buff *skb, int *ns, int *nr, int *q, int *d, int *m)
{
	unsigned char *frame;

	frame = skb->data;

	*ns = *nr = *q = *d = *m = 0;

	switch (frame[2]) {
	case ROSE_CALL_REQUEST:
	case ROSE_CALL_ACCEPTED:
	case ROSE_CLEAR_REQUEST:
	case ROSE_CLEAR_CONFIRMATION:
	case ROSE_RESET_REQUEST:
	case ROSE_RESET_CONFIRMATION:
		return frame[2];
	default:
		break;
	}

	if ((frame[2] & 0x1F) == ROSE_RR  ||
	    (frame[2] & 0x1F) == ROSE_RNR) {
		*nr = (frame[2] >> 5) & 0x07;
		return frame[2] & 0x1F;
	}

	if ((frame[2] & 0x01) == ROSE_DATA) {
		*q  = (frame[0] & ROSE_Q_BIT) == ROSE_Q_BIT;
		*d  = (frame[0] & ROSE_D_BIT) == ROSE_D_BIT;
		*m  = (frame[2] & ROSE_M_BIT) == ROSE_M_BIT;
		*nr = (frame[2] >> 5) & 0x07;
		*ns = (frame[2] >> 1) & 0x07;
		return ROSE_DATA;
	}

	return ROSE_ILLEGAL;
}