#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  rtfMinor; } ;
typedef  TYPE_1__ RTF_Info ;

/* Variables and functions */
 int /*<<< orphan*/  RTFGetDestinationCallback (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTFSkipGroup (TYPE_1__*) ; 

__attribute__((used)) static void
Destination (RTF_Info *info)
{
	if (!RTFGetDestinationCallback(info, info->rtfMinor))
		RTFSkipGroup (info);    
}