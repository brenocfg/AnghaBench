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
typedef  unsigned int txid ;

/* Variables and functions */
 int MAX_TXID ; 

__attribute__((used)) static txid
str2txid(const char *s, const char **endp)
{
	txid		val = 0;
	txid		cutoff = MAX_TXID / 10;
	txid		cutlim = MAX_TXID % 10;

	for (; *s; s++)
	{
		unsigned	d;

		if (*s < '0' || *s > '9')
			break;
		d = *s - '0';

		/*
		 * check for overflow
		 */
		if (val > cutoff || (val == cutoff && d > cutlim))
		{
			val = 0;
			break;
		}

		val = val * 10 + d;
	}
	if (endp)
		*endp = s;
	return val;
}