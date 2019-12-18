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

/* Variables and functions */
 int PG_UTF8 ; 
 int /*<<< orphan*/  mb_utf_validate (unsigned char*) ; 

unsigned char *
mbvalidate(unsigned char *pwcs, int encoding)
{
	if (encoding == PG_UTF8)
		mb_utf_validate(pwcs);
	else
	{
		/*
		 * other encodings needing validation should add their own routines
		 * here
		 */
	}

	return pwcs;
}