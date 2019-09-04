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
struct RtfData {scalar_t__ ptr; scalar_t__ data; int allocated; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,size_t) ; 

__attribute__((used)) static BOOL HLPFILE_RtfAddRawString(struct RtfData* rd, const char* str, size_t sz)
{
    if (rd->ptr + sz >= rd->data + rd->allocated)
    {
        char*   new = HeapReAlloc(GetProcessHeap(), 0, rd->data, rd->allocated *= 2);
        if (!new) return FALSE;
        rd->ptr = new + (rd->ptr - rd->data);
        rd->data = new;
    }
    memcpy(rd->ptr, str, sz);
    rd->ptr += sz;

    return TRUE;
}