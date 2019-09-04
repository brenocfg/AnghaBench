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
struct isi_port {int channel; int /*<<< orphan*/  status; struct isi_board* card; } ;
struct isi_board {unsigned long base; int shift_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISI_RTS ; 
 int /*<<< orphan*/  InterruptTheCard (unsigned long) ; 
 scalar_t__ WaitTillCardIsFree (unsigned long) ; 
 int /*<<< orphan*/  outw (int,unsigned long) ; 

__attribute__((used)) static inline void raise_rts(struct isi_port *port)
{
	struct isi_board *card = port->card;
	unsigned long base = card->base;
	u16 channel = port->channel;

	if (WaitTillCardIsFree(base))
		return;

	outw(0x8000 | (channel << card->shift_count) | 0x02, base);
	outw(0x0a04, base);
	InterruptTheCard(base);
	port->status |= ISI_RTS;
}