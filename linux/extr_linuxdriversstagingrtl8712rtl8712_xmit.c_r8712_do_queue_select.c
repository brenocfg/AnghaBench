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
struct pkt_attrib {unsigned int qsel; scalar_t__ priority; } ;
struct dvobj_priv {int nr_endpoint; } ;
struct _adapter {struct dvobj_priv dvobjpriv; } ;

/* Variables and functions */

void r8712_do_queue_select(struct _adapter *padapter,
			   struct pkt_attrib *pattrib)
{
	unsigned int qsel = 0;
	struct dvobj_priv *pdvobj = &padapter->dvobjpriv;

	if (pdvobj->nr_endpoint == 6) {
		qsel = (unsigned int) pattrib->priority;
	} else if (pdvobj->nr_endpoint == 4) {
		qsel = (unsigned int) pattrib->priority;
		if (qsel == 0 || qsel == 3)
			qsel = 3;
		else if (qsel == 1 || qsel == 2)
			qsel = 1;
		else if (qsel == 4 || qsel == 5)
			qsel = 5;
		else if (qsel == 6 || qsel == 7)
			qsel = 7;
		else
			qsel = 3;
	}
	pattrib->qsel = qsel;
}