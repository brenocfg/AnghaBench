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
struct TYPE_6__ {int /*<<< orphan*/  domain_info; TYPE_3__* base; } ;
struct TYPE_7__ {TYPE_1__ domain; } ;
struct TYPE_8__ {int /*<<< orphan*/  mcxt; TYPE_2__ u; int /*<<< orphan*/  typoid; int /*<<< orphan*/  (* func ) (TYPE_3__*,int /*<<< orphan*/ *,int*,int) ;} ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_3__ PLyObToDatum ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  domain_check (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static Datum
PLyObject_ToDomain(PLyObToDatum *arg, PyObject *plrv,
				   bool *isnull, bool inarray)
{
	Datum		result;
	PLyObToDatum *base = arg->u.domain.base;

	result = base->func(base, plrv, isnull, inarray);
	domain_check(result, *isnull, arg->typoid,
				 &arg->u.domain.domain_info, arg->mcxt);
	return result;
}