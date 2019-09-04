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
typedef  char u_char ;
struct TYPE_5__ {char* TupleData; int TupleDataLen; } ;
typedef  TYPE_1__ tuple_t ;
struct TYPE_6__ {char data_org; char* desc; } ;
typedef  TYPE_2__ cistpl_org_t ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int parse_org(tuple_t *tuple, cistpl_org_t *org)
{
	u_char *p, *q;
	int i;

	p = tuple->TupleData;
	q = p + tuple->TupleDataLen;
	if (p == q)
		return -EINVAL;
	org->data_org = *p;
	if (++p == q)
		return -EINVAL;
	for (i = 0; i < 30; i++) {
		org->desc[i] = *p;
		if (*p == '\0')
			break;
		if (++p == q)
			return -EINVAL;
	}
	return 0;
}