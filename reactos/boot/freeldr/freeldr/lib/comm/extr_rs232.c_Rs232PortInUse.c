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
struct TYPE_2__ {scalar_t__ Address; } ;
typedef  scalar_t__ PUCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ Rs232ComPort ; 
 TYPE_1__ Rs232ComPortInfo ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN Rs232PortInUse(PUCHAR Base)
{
#if DBG
    return ( ((Rs232ComPort != 0) && (Rs232ComPortInfo.Address == Base)) ? TRUE : FALSE );
#else
    return FALSE;
#endif
}