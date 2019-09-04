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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_2__ {scalar_t__ hEvent; } ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  FlushFileBuffers (scalar_t__) ; 
 scalar_t__ hLogFile ; 
 TYPE_1__ olWrite ; 

VOID
UninitLogging()
{
    if (hLogFile)
    {
        FlushFileBuffers(hLogFile);
        CloseHandle(hLogFile);
    }

    if (olWrite.hEvent)
    {
        CloseHandle(olWrite.hEvent);
    }
}