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

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,scalar_t__ const,scalar_t__ const) ; 

__attribute__((used)) static int comp_tics (const void *ap, const void *bp)
{
    const DWORD a = *(const DWORD *)ap;
    const DWORD b = *(const DWORD *)bp;

    TRACE("(a=%d, b=%d)\n", a, b);
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}