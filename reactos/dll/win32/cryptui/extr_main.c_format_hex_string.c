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
typedef  char WCHAR ;
typedef  int DWORD ;
typedef  char* BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  swprintf (char*,char const*,char*) ; 

__attribute__((used)) static WCHAR *format_hex_string(void *pb, DWORD cb)
{
    WCHAR *buf = HeapAlloc(GetProcessHeap(), 0, (cb * 3 + 1) * sizeof(WCHAR));

    if (buf)
    {
        static const WCHAR fmt[] = { '%','0','2','x',' ',0 };
        DWORD i;
        WCHAR *ptr;

        for (i = 0, ptr = buf; i < cb; i++, ptr += 3)
            swprintf(ptr, fmt, ((BYTE *)pb)[i]);
    }
    return buf;
}