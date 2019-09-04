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
typedef  int wchar_t ;

/* Variables and functions */
 int** toplevel ; 

wchar_t
cifs_toupper(wchar_t in)
{
	unsigned char idx;
	const wchar_t *tbl;
	wchar_t out;

	/* grab upper byte */
	idx = (in & 0xff00) >> 8;

	/* find pointer to 2nd layer table */
	tbl = toplevel[idx];
	if (!tbl)
		return in;

	/* grab lower byte */
	idx = in & 0xff;

	/* look up character in table */
	out = tbl[idx];
	if (out)
		return out;

	return in;
}