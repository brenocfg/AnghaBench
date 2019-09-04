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
struct TYPE_5__ {int /*<<< orphan*/  statusdir; int /*<<< orphan*/  status; int /*<<< orphan*/  datadir; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_2__ amiga; } ;
struct parport_state {TYPE_1__ u; } ;
struct parport {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  cra; int /*<<< orphan*/  pddrb; int /*<<< orphan*/  ppra; int /*<<< orphan*/  crb; int /*<<< orphan*/  pprb; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIA_DDR ; 
 TYPE_3__* pia (struct parport*) ; 

__attribute__((used)) static void mfc3_save_state(struct parport *p, struct parport_state *s)
{
	s->u.amiga.data = pia(p)->pprb;
	pia(p)->crb &= ~PIA_DDR;
	s->u.amiga.datadir = pia(p)->pddrb;
	pia(p)->crb |= PIA_DDR;
	s->u.amiga.status = pia(p)->ppra;
	pia(p)->cra &= ~PIA_DDR;
	s->u.amiga.statusdir = pia(p)->pddrb;
	pia(p)->cra |= PIA_DDR;
}