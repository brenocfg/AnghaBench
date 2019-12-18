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
struct TYPE_6__ {TYPE_1__* paramDescs; } ;
struct TYPE_5__ {int /*<<< orphan*/  typid; } ;
typedef  TYPE_2__ PGresult ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  check_param_number (TYPE_2__ const*,int) ; 

Oid
PQparamtype(const PGresult *res, int param_num)
{
	if (!check_param_number(res, param_num))
		return InvalidOid;
	if (res->paramDescs)
		return res->paramDescs[param_num].typid;
	else
		return InvalidOid;
}