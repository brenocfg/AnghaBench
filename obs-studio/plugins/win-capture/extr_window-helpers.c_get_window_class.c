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
typedef  scalar_t__ wchar_t ;
typedef  int /*<<< orphan*/  temp ;
struct dstr {int dummy; } ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 scalar_t__ GetClassNameW (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  dstr_from_wcs (struct dstr*,scalar_t__*) ; 

void get_window_class(struct dstr *class, HWND hwnd)
{
	wchar_t temp[256];

	temp[0] = 0;
	if (GetClassNameW(hwnd, temp, sizeof(temp) / sizeof(wchar_t)))
		dstr_from_wcs(class, temp);
}