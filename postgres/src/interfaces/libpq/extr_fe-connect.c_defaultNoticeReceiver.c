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
struct TYPE_5__ {int /*<<< orphan*/  noticeProcArg; int /*<<< orphan*/  (* noticeProc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_1__ noticeHooks; } ;
typedef  TYPE_2__ PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  PQresultErrorMessage (TYPE_2__ const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
defaultNoticeReceiver(void *arg, const PGresult *res)
{
	(void) arg;					/* not used */
	if (res->noticeHooks.noticeProc != NULL)
		res->noticeHooks.noticeProc(res->noticeHooks.noticeProcArg,
									PQresultErrorMessage(res));
}