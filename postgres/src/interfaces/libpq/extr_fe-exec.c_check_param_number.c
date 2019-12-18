#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int numParameters; int /*<<< orphan*/  noticeHooks; } ;
typedef  TYPE_1__ PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  pqInternalNotice (int /*<<< orphan*/ *,char*,int,int) ; 

__attribute__((used)) static int
check_param_number(const PGresult *res, int param_num)
{
	if (!res)
		return false;			/* no way to display error message... */
	if (param_num < 0 || param_num >= res->numParameters)
	{
		pqInternalNotice(&res->noticeHooks,
						 "parameter number %d is out of range 0..%d",
						 param_num, res->numParameters - 1);
		return false;
	}

	return true;
}