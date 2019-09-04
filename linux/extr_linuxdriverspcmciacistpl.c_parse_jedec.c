#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_char ;
struct TYPE_7__ {int TupleDataLen; scalar_t__ TupleData; } ;
typedef  TYPE_2__ tuple_t ;
struct TYPE_8__ {int nid; TYPE_1__* id; } ;
typedef  TYPE_3__ cistpl_jedec_t ;
struct TYPE_6__ {void* info; void* mfr; } ;

/* Variables and functions */
 int CISTPL_MAX_DEVICES ; 

__attribute__((used)) static int parse_jedec(tuple_t *tuple, cistpl_jedec_t *jedec)
{
	u_char *p, *q;
	int nid;

	p = (u_char *)tuple->TupleData;
	q = p + tuple->TupleDataLen;

	for (nid = 0; nid < CISTPL_MAX_DEVICES; nid++) {
		if (p > q-2)
			break;
		jedec->id[nid].mfr = p[0];
		jedec->id[nid].info = p[1];
		p += 2;
	}
	jedec->nid = nid;
	return 0;
}