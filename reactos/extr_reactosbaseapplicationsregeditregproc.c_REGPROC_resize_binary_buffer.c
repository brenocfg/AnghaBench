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
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ENOUGH_MEMORY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void REGPROC_resize_binary_buffer(BYTE **buffer, DWORD *size, DWORD required_size)
{
    if (required_size > *size) {
        *size = required_size;
        if (!*buffer)
            *buffer = HeapAlloc(GetProcessHeap(), 0, *size);
        else
            *buffer = HeapReAlloc(GetProcessHeap(), 0, *buffer, *size);
        CHECK_ENOUGH_MEMORY(*buffer);
    }
}