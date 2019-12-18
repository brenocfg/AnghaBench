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
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lstrcpyA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lstrlenA (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline LPSTR dns_strdup_a( LPCSTR src )
{
    LPSTR dst;

    if (!src) return NULL;
    dst = HeapAlloc(GetProcessHeap(), 0, (lstrlenA( src ) + 1) * sizeof(char) );
    if (dst) lstrcpyA( dst, src );
    return dst;
}