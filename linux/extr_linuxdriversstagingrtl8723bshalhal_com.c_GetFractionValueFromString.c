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
typedef  int u8 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */

bool GetFractionValueFromString(
	char *szStr, u8 *pInteger, u8 *pFraction, u32 *pu4bMove
)
{
	char *szScan = szStr;

	/*  Initialize output. */
	*pu4bMove = 0;
	*pInteger = 0;
	*pFraction = 0;

	/*  Skip leading space. */
	while (*szScan != '\0' &&	(*szScan == ' ' || *szScan == '\t')) {
		++szScan;
		++(*pu4bMove);
	}

	/*  Parse each digit. */
	do {
		(*pInteger) *= 10;
		*pInteger += (*szScan - '0');

		++szScan;
		++(*pu4bMove);

		if (*szScan == '.') {
			++szScan;
			++(*pu4bMove);

			if (*szScan < '0' || *szScan > '9')
				return false;
			else {
				*pFraction = *szScan - '0';
				++szScan;
				++(*pu4bMove);
				return true;
			}
		}
	} while (*szScan >= '0' && *szScan <= '9');

	return true;
}