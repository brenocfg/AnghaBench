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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (void*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL copy_value(const char *ptr, void **value, DWORD size)
{
    if (!ptr || !size) return TRUE;

    *value = HeapAlloc(GetProcessHeap(), 0, size);
    if (!*value)
    {
        ERR("Failed to allocate value memory.\n");
        return FALSE;
    }

    memcpy(*value, ptr, size);

    return TRUE;
}