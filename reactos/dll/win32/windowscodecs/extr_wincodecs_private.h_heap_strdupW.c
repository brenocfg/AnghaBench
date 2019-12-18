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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int SIZE_T ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int strlenW (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline WCHAR *heap_strdupW(const WCHAR *src)
{
    WCHAR *dst;
    SIZE_T len;
    if (!src) return NULL;
    len = (strlenW(src) + 1) * sizeof(WCHAR);
    if ((dst = HeapAlloc(GetProcessHeap(), 0, len))) memcpy(dst, src, len);
    return dst;
}