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
struct TYPE_6__ {TYPE_1__* attDescs; } ;
struct TYPE_5__ {int typlen; } ;
typedef  TYPE_2__ PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  check_field_number (TYPE_2__ const*,int) ; 

int
PQfsize(const PGresult *res, int field_num)
{
	if (!check_field_number(res, field_num))
		return 0;
	if (res->attDescs)
		return res->attDescs[field_num].typlen;
	else
		return 0;
}