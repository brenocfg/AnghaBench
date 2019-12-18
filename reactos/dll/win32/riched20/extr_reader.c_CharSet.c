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
struct TYPE_3__ {scalar_t__ ansiCodePage; int rtfMinor; } ;
typedef  TYPE_1__ RTF_Info ;

/* Variables and functions */
 scalar_t__ CP_UTF8 ; 
#define  rtfAnsiCharSet 131 
#define  rtfMacCharSet 130 
#define  rtfPcCharSet 129 
#define  rtfPcaCharSet 128 

__attribute__((used)) static void
CharSet(RTF_Info *info)
{
	if (info->ansiCodePage == CP_UTF8)
		return;
 
        switch (info->rtfMinor)
        {
        case rtfAnsiCharSet:
                info->ansiCodePage = 1252; /* Latin-1 */
                break;
        case rtfMacCharSet:
                info->ansiCodePage = 10000; /* MacRoman */
                break;
        case rtfPcCharSet:
                info->ansiCodePage = 437;
                break;
        case rtfPcaCharSet:
                info->ansiCodePage = 850;
                break;
        }
}