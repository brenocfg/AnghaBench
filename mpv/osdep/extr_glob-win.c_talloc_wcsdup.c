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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/ * talloc_memdup (void*,void*,size_t) ; 
 int wcslen (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static wchar_t *talloc_wcsdup(void *ctx, const wchar_t *wcs)
{
    size_t len = (wcslen(wcs) + 1) * sizeof(wchar_t);
    return talloc_memdup(ctx, (void*)wcs, len);
}