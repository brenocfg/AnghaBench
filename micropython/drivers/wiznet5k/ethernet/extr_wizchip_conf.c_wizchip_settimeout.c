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
struct TYPE_3__ {int /*<<< orphan*/  time_100us; int /*<<< orphan*/  retry_cnt; } ;
typedef  TYPE_1__ wiz_NetTimeout ;

/* Variables and functions */
 int /*<<< orphan*/  setRCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setRTR (int /*<<< orphan*/ ) ; 

void wizchip_settimeout(wiz_NetTimeout* nettime)
{
   setRCR(nettime->retry_cnt);
   setRTR(nettime->time_100us);
}