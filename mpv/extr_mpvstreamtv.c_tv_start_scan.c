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
struct TYPE_6__ {TYPE_1__* tv_param; } ;
typedef  TYPE_2__ tvi_handle_t ;
struct TYPE_5__ {int scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_INFO (TYPE_2__*,char*) ; 

void tv_start_scan(tvi_handle_t *tvh, int start)
{
    MP_INFO(tvh, "start scan\n");
    tvh->tv_param->scan=start?1:0;
}