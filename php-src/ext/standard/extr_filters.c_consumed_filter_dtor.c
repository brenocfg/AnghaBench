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
struct TYPE_5__ {int /*<<< orphan*/  abstract; } ;
typedef  TYPE_1__ php_stream_filter ;
struct TYPE_6__ {int /*<<< orphan*/  persistent; } ;
typedef  TYPE_2__ php_consumed_filter_data ;

/* Variables and functions */
 scalar_t__ Z_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pefree (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void consumed_filter_dtor(php_stream_filter *thisfilter)
{
	if (thisfilter && Z_PTR(thisfilter->abstract)) {
		php_consumed_filter_data *data = (php_consumed_filter_data*)Z_PTR(thisfilter->abstract);
		pefree(data, data->persistent);
	}
}