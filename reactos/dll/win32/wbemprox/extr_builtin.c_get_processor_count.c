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
typedef  int /*<<< orphan*/  info ;
typedef  int UINT ;
struct TYPE_3__ {int NumberOfProcessors; } ;
typedef  TYPE_1__ SYSTEM_BASIC_INFORMATION ;

/* Variables and functions */
 scalar_t__ NtQuerySystemInformation (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SystemBasicInformation ; 

__attribute__((used)) static UINT get_processor_count(void)
{
    SYSTEM_BASIC_INFORMATION info;

    if (NtQuerySystemInformation( SystemBasicInformation, &info, sizeof(info), NULL )) return 1;
    return info.NumberOfProcessors;
}