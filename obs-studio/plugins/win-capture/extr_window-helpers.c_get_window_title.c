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
struct dstr {int dummy; } ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int GetWindowTextLengthW (int /*<<< orphan*/ ) ; 
 scalar_t__ GetWindowTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dstr_from_wcs (struct dstr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 

void get_window_title(struct dstr *name, HWND hwnd)
{
	wchar_t *temp;
	int len;

	len = GetWindowTextLengthW(hwnd);
	if (!len)
		return;

	temp = malloc(sizeof(wchar_t) * (len + 1));
	if (GetWindowTextW(hwnd, temp, len + 1))
		dstr_from_wcs(name, temp);
	free(temp);
}