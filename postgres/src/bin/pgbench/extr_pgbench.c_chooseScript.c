#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64 ;
struct TYPE_5__ {scalar_t__ weight; } ;
struct TYPE_4__ {int /*<<< orphan*/  ts_choose_rs; } ;
typedef  TYPE_1__ TState ;

/* Variables and functions */
 scalar_t__ getrand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int num_scripts ; 
 TYPE_2__* sql_script ; 
 scalar_t__ total_weight ; 

__attribute__((used)) static int
chooseScript(TState *thread)
{
	int			i = 0;
	int64		w;

	if (num_scripts == 1)
		return 0;

	w = getrand(&thread->ts_choose_rs, 0, total_weight - 1);
	do
	{
		w -= sql_script[i++].weight;
	} while (w >= 0);

	return i - 1;
}