#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ rtfClass; } ;
typedef  TYPE_1__ RTF_Info ;

/* Variables and functions */
 scalar_t__ RTFCheckCM (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTFGetToken (TYPE_1__*) ; 
 int /*<<< orphan*/  RTFRouteToken (TYPE_1__*) ; 
 int /*<<< orphan*/  rtfBeginGroup ; 
 scalar_t__ rtfEOF ; 
 int /*<<< orphan*/  rtfEndGroup ; 
 int /*<<< orphan*/  rtfGroup ; 

__attribute__((used)) static void ME_RTFReadShpPictGroup( RTF_Info *info )
{
    int level = 1;

    for (;;)
    {
        RTFGetToken (info);

        if (info->rtfClass == rtfEOF) return;
        if (RTFCheckCM( info, rtfGroup, rtfEndGroup ))
        {
            if (--level == 0) break;
        }
        else if (RTFCheckCM( info, rtfGroup, rtfBeginGroup ))
        {
            level++;
        }
        else
        {
            RTFRouteToken( info );
            if (RTFCheckCM( info, rtfGroup, rtfEndGroup ))
                level--;
        }
    }

    RTFRouteToken( info ); /* feed "}" back to router */
    return;
}