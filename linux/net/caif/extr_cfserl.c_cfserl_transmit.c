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
typedef  int /*<<< orphan*/  u8 ;
struct cfserl {scalar_t__ usestx; } ;
struct cfpkt {int dummy; } ;
struct cflayer {TYPE_1__* dn; } ;
struct TYPE_2__ {int (* transmit ) (TYPE_1__*,struct cfpkt*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CFSERL_STX ; 
 int /*<<< orphan*/  cfpkt_add_head (struct cfpkt*,int /*<<< orphan*/ *,int) ; 
 struct cfserl* container_obj (struct cflayer*) ; 
 int stub1 (TYPE_1__*,struct cfpkt*) ; 

__attribute__((used)) static int cfserl_transmit(struct cflayer *layer, struct cfpkt *newpkt)
{
	struct cfserl *layr = container_obj(layer);
	u8 tmp8 = CFSERL_STX;
	if (layr->usestx)
		cfpkt_add_head(newpkt, &tmp8, 1);
	return layer->dn->transmit(layer->dn, newpkt);
}