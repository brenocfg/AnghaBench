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
struct TYPE_2__ {int m_iExtraChildren; } ;

/* Variables and functions */
 TYPE_1__* g_prefork_server ; 

void LSAPI_Set_Extra_Children( int extraChildren )
{
    if (( g_prefork_server )&&( extraChildren >= 0 ))
        g_prefork_server->m_iExtraChildren = extraChildren;
}