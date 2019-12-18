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
typedef  int u8 ;
struct cfpkt {int dummy; } ;
struct cflayer {TYPE_1__* up; } ;
struct TYPE_2__ {int (* receive ) (TYPE_1__*,struct cfpkt*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cfpkt_extr_head (struct cfpkt*,int*,int) ; 
 int stub1 (TYPE_1__*,struct cfpkt*) ; 

__attribute__((used)) static int cfusbl_receive(struct cflayer *layr, struct cfpkt *pkt)
{
	u8 hpad;

	/* Remove padding. */
	cfpkt_extr_head(pkt, &hpad, 1);
	cfpkt_extr_head(pkt, NULL, hpad);
	return layr->up->receive(layr->up, pkt);
}