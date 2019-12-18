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
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int _wcsicmp (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

int compare(const void *x, const void *y)
{
    const LPCWSTR *a = (const LPCWSTR *)x;
    const LPCWSTR *b = (const LPCWSTR *)y;
    return _wcsicmp(*a, *b);
}