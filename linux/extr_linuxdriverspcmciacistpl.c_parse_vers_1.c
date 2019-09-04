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
struct TYPE_6__ {int /*<<< orphan*/  ns; int /*<<< orphan*/  ofs; int /*<<< orphan*/  str; void* minor; void* major; } ;
typedef  TYPE_2__ cistpl_vers_1_t ;

/* Variables and functions */
 int /*<<< orphan*/  CISTPL_VERS_1_MAX_PROD_STRINGS ; 
 int EINVAL ; 
 int parse_strings (void**,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_vers_1(tuple_t *tuple, cistpl_vers_1_t *vers_1)
{
	u_char *p, *q;

	p = (u_char *)tuple->TupleData;
	q = p + tuple->TupleDataLen;

	vers_1->major = *p; p++;
	vers_1->minor = *p; p++;
	if (p >= q)
		return -EINVAL;

	return parse_strings(p, q, CISTPL_VERS_1_MAX_PROD_STRINGS,
			vers_1->str, vers_1->ofs, &vers_1->ns);
}