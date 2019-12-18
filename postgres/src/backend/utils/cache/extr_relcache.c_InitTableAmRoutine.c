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
struct TYPE_3__ {int /*<<< orphan*/  rd_amhandler; int /*<<< orphan*/  rd_tableam; } ;
typedef  TYPE_1__* Relation ;

/* Variables and functions */
 int /*<<< orphan*/  GetTableAmRoutine (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
InitTableAmRoutine(Relation relation)
{
	relation->rd_tableam = GetTableAmRoutine(relation->rd_amhandler);
}