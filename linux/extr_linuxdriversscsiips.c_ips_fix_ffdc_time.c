#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time64_t ;
struct tm {int tm_year; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; } ;
struct TYPE_5__ {int yearH; int yearL; int /*<<< orphan*/  day; scalar_t__ month; int /*<<< orphan*/  second; int /*<<< orphan*/  minute; int /*<<< orphan*/  hour; } ;
struct TYPE_6__ {TYPE_1__ ffdc; } ;
struct TYPE_7__ {TYPE_2__ cmd; } ;
typedef  TYPE_3__ ips_scb_t ;
typedef  int /*<<< orphan*/  ips_ha_t ;

/* Variables and functions */
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int /*<<< orphan*/  time64_to_tm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tm*) ; 

__attribute__((used)) static void
ips_fix_ffdc_time(ips_ha_t * ha, ips_scb_t * scb, time64_t current_time)
{
	struct tm tm;

	METHOD_TRACE("ips_fix_ffdc_time", 1);

	time64_to_tm(current_time, 0, &tm);

	scb->cmd.ffdc.hour   = tm.tm_hour;
	scb->cmd.ffdc.minute = tm.tm_min;
	scb->cmd.ffdc.second = tm.tm_sec;
	scb->cmd.ffdc.yearH  = (tm.tm_year + 1900) / 100;
	scb->cmd.ffdc.yearL  = tm.tm_year % 100;
	scb->cmd.ffdc.month  = tm.tm_mon + 1;
	scb->cmd.ffdc.day    = tm.tm_mday;
}