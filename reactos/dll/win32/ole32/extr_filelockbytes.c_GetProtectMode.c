#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_READONLY ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int STGM_ACCESS_MODE (int /*<<< orphan*/ ) ; 
#define  STGM_READWRITE 129 
#define  STGM_WRITE 128 

__attribute__((used)) static DWORD GetProtectMode(DWORD openFlags)
{
    switch(STGM_ACCESS_MODE(openFlags))
    {
    case STGM_WRITE:
    case STGM_READWRITE:
        return PAGE_READWRITE;
    }
    return PAGE_READONLY;
}