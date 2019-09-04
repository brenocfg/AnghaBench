#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_6__ {scalar_t__ slottime; int ppersist; scalar_t__ fulldup; } ;
struct TYPE_5__ {scalar_t__ slotcnt; scalar_t__ ptt; } ;
struct TYPE_4__ {scalar_t__ dcd; } ;
struct hdlcdrv_state {scalar_t__ magic; TYPE_3__ ch_params; TYPE_2__ hdlctx; TYPE_1__ hdlcrx; int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 scalar_t__ HDLCDRV_MAGIC ; 
 int prandom_u32 () ; 
 int /*<<< orphan*/  start_tx (struct net_device*,struct hdlcdrv_state*) ; 

void hdlcdrv_arbitrate(struct net_device *dev, struct hdlcdrv_state *s)
{
	if (!s || s->magic != HDLCDRV_MAGIC || s->hdlctx.ptt || !s->skb) 
		return;
	if (s->ch_params.fulldup) {
		start_tx(dev, s);
		return;
	}
	if (s->hdlcrx.dcd) {
		s->hdlctx.slotcnt = s->ch_params.slottime;
		return;
	}
	if ((--s->hdlctx.slotcnt) > 0)
		return;
	s->hdlctx.slotcnt = s->ch_params.slottime;
	if ((prandom_u32() % 256) > s->ch_params.ppersist)
		return;
	start_tx(dev, s);
}