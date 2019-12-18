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
struct TYPE_7__ {TYPE_2__* style; } ;
struct TYPE_5__ {int dwMask; int dwEffects; } ;
struct TYPE_6__ {TYPE_1__ fmt; } ;
typedef  TYPE_3__ ME_Run ;
typedef  int BOOL ;

/* Variables and functions */
 int CFE_LINK ; 
 int CFM_LINK ; 

__attribute__((used)) static BOOL is_link( ME_Run *run )
{
    return (run->style->fmt.dwMask & CFM_LINK) && (run->style->fmt.dwEffects & CFE_LINK);
}