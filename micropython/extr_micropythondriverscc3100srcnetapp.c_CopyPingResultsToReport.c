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
struct TYPE_5__ {int /*<<< orphan*/  testTime; int /*<<< orphan*/  rttAvg; int /*<<< orphan*/  rttMax; int /*<<< orphan*/  rttMin; int /*<<< orphan*/  numSuccsessPings; int /*<<< orphan*/  numSendsPings; } ;
typedef  TYPE_1__ _PingReportResponse_t ;
struct TYPE_6__ {int /*<<< orphan*/  TestTime; int /*<<< orphan*/  AvgRoundTime; int /*<<< orphan*/  MaxRoundTime; int /*<<< orphan*/  MinRoundTime; int /*<<< orphan*/  PacketsReceived; int /*<<< orphan*/  PacketsSent; } ;
typedef  TYPE_2__ SlPingReport_t ;

/* Variables and functions */

void CopyPingResultsToReport(_PingReportResponse_t *pResults,SlPingReport_t *pReport)
{
    pReport->PacketsSent     = pResults->numSendsPings;
    pReport->PacketsReceived = pResults->numSuccsessPings;
    pReport->MinRoundTime    = pResults->rttMin;
    pReport->MaxRoundTime    = pResults->rttMax;
    pReport->AvgRoundTime    = pResults->rttAvg;
    pReport->TestTime        = pResults->testTime;
}