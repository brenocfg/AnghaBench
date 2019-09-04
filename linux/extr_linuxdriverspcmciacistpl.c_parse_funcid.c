#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_char ;
struct TYPE_5__ {int TupleDataLen; scalar_t__ TupleData; } ;
typedef  TYPE_1__ tuple_t ;
struct TYPE_6__ {void* sysinit; void* func; } ;
typedef  TYPE_2__ cistpl_funcid_t ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int parse_funcid(tuple_t *tuple, cistpl_funcid_t *f)
{
	u_char *p;
	if (tuple->TupleDataLen < 2)
		return -EINVAL;
	p = (u_char *)tuple->TupleData;
	f->func = p[0];
	f->sysinit = p[1];
	return 0;
}