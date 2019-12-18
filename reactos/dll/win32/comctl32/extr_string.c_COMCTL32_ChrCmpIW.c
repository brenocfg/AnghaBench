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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CSTR_EQUAL ; 
 scalar_t__ CompareStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetThreadLocale () ; 
 int /*<<< orphan*/  NORM_IGNORECASE ; 

__attribute__((used)) static inline BOOL COMCTL32_ChrCmpIW(WCHAR ch1, WCHAR ch2)
{
  return CompareStringW(GetThreadLocale(), NORM_IGNORECASE, &ch1, 1, &ch2, 1) - CSTR_EQUAL;
}