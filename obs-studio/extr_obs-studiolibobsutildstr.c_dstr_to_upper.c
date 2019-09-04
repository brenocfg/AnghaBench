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
struct dstr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (scalar_t__*) ; 
 int /*<<< orphan*/  dstr_from_wcs (struct dstr*,scalar_t__*) ; 
 scalar_t__ dstr_is_empty (struct dstr*) ; 
 scalar_t__* dstr_to_wcs (struct dstr*) ; 
 scalar_t__ towupper (scalar_t__) ; 

void dstr_to_upper(struct dstr *str)
{
	wchar_t *wstr;
	wchar_t *temp;

	if (dstr_is_empty(str))
		return;

	wstr = dstr_to_wcs(str);
	temp = wstr;

	if (!wstr)
		return;

	while (*temp) {
		*temp = (wchar_t)towupper(*temp);
		temp++;
	}

	dstr_from_wcs(str, wstr);
	bfree(wstr);
}