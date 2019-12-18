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
struct TYPE_3__ {int /*<<< orphan*/  extstats; int /*<<< orphan*/  alist; } ;
typedef  TYPE_1__ CreateStmtContext ;

/* Variables and functions */
 int /*<<< orphan*/  list_concat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
transformExtendedStatistics(CreateStmtContext *cxt)
{
	cxt->alist = list_concat(cxt->alist, cxt->extstats);
}