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
typedef  int /*<<< orphan*/  int32 ;

/* Variables and functions */
 char* getsecs (char const*,int /*<<< orphan*/ * const) ; 

__attribute__((used)) static const char *
getoffset(const char *strp, int32 *const offsetp)
{
	bool		neg = false;

	if (*strp == '-')
	{
		neg = true;
		++strp;
	}
	else if (*strp == '+')
		++strp;
	strp = getsecs(strp, offsetp);
	if (strp == NULL)
		return NULL;			/* illegal time */
	if (neg)
		*offsetp = -*offsetp;
	return strp;
}