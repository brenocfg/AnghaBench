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
typedef  size_t UINT ;
struct TYPE_5__ {size_t MaxMhz; } ;
typedef  TYPE_1__ PROCESSOR_POWER_INFORMATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  NtPowerInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  ProcessorInformation ; 
 int get_processor_count () ; 
 TYPE_1__* heap_alloc (size_t) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 

__attribute__((used)) static UINT get_processor_maxclockspeed( UINT index )
{
    PROCESSOR_POWER_INFORMATION *info;
    UINT ret = 1000, size = get_processor_count() * sizeof(PROCESSOR_POWER_INFORMATION);
    NTSTATUS status;

    if ((info = heap_alloc( size )))
    {
        status = NtPowerInformation( ProcessorInformation, NULL, 0, info, size );
        if (!status) ret = info[index].MaxMhz;
        heap_free( info );
    }
    return ret;
}