#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct evsel {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* process_stat ) (int /*<<< orphan*/ *,struct evsel*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __process_stat (struct evsel*,int /*<<< orphan*/ ) ; 
 TYPE_1__* scripting_ops ; 
 int /*<<< orphan*/  stat_config ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct evsel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_stat(struct evsel *counter, u64 tstamp)
{
	if (scripting_ops && scripting_ops->process_stat)
		scripting_ops->process_stat(&stat_config, counter, tstamp);
	else
		__process_stat(counter, tstamp);
}