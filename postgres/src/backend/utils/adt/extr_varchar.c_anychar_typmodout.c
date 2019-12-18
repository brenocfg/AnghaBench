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
typedef  scalar_t__ int32 ;

/* Variables and functions */
 scalar_t__ VARHDRSZ ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static char *
anychar_typmodout(int32 typmod)
{
	char	   *res = (char *) palloc(64);

	if (typmod > VARHDRSZ)
		snprintf(res, 64, "(%d)", (int) (typmod - VARHDRSZ));
	else
		*res = '\0';

	return res;
}