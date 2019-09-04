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
typedef  int uint ;
struct channel_t {int ch_w_head; scalar_t__ ch_wqueue; } ;

/* Variables and functions */
 int WQUEUEMASK ; 
 int WQUEUESIZE ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,int) ; 

__attribute__((used)) static void dgnc_wmove(struct channel_t *ch, char *buf, uint n)
{
	int	remain;
	uint	head;

	if (!ch)
		return;

	head = ch->ch_w_head & WQUEUEMASK;

	/*
	 * If the write wraps over the top of the circular buffer,
	 * move the portion up to the wrap point, and reset the
	 * pointers to the bottom.
	 */
	remain = WQUEUESIZE - head;

	if (n >= remain) {
		n -= remain;
		memcpy(ch->ch_wqueue + head, buf, remain);
		head = 0;
		buf += remain;
	}

	if (n > 0) {
		/* Move rest of data. */
		remain = n;
		memcpy(ch->ch_wqueue + head, buf, remain);
		head += remain;
	}

	head &= WQUEUEMASK;
	ch->ch_w_head = head;
}