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
 int /*<<< orphan*/  isdigit (unsigned char) ; 

__attribute__((used)) static unsigned
hyphenate(char *bufO, char *bufI, const char *(*TABLE)[2], const unsigned TABLE_index[10][2])
{
	unsigned	ret = 0;
	const char *ean_aux1,
			   *ean_aux2,
			   *ean_p;
	char	   *firstdig,
			   *aux1,
			   *aux2;
	unsigned	search,
				upper,
				lower,
				step;
	bool		ean_in1,
				ean_in2;

	/* just compress the string if no further hyphenation is required */
	if (TABLE == NULL || TABLE_index == NULL)
	{
		while (*bufI)
		{
			*bufO++ = *bufI++;
			ret++;
		}
		*bufO = '\0';
		return (ret + 1);
	}

	/* add remaining hyphenations */

	search = *bufI - '0';
	upper = lower = TABLE_index[search][0];
	upper += TABLE_index[search][1];
	lower--;

	step = (upper - lower) / 2;
	if (step == 0)
		return 0;
	search = lower + step;

	firstdig = bufI;
	ean_in1 = ean_in2 = false;
	ean_aux1 = TABLE[search][0];
	ean_aux2 = TABLE[search][1];
	do
	{
		if ((ean_in1 || *firstdig >= *ean_aux1) && (ean_in2 || *firstdig <= *ean_aux2))
		{
			if (*firstdig > *ean_aux1)
				ean_in1 = true;
			if (*firstdig < *ean_aux2)
				ean_in2 = true;
			if (ean_in1 && ean_in2)
				break;

			firstdig++, ean_aux1++, ean_aux2++;
			if (!(*ean_aux1 && *ean_aux2 && *firstdig))
				break;
			if (!isdigit((unsigned char) *ean_aux1))
				ean_aux1++, ean_aux2++;
		}
		else
		{
			/*
			 * check in what direction we should go and move the pointer
			 * accordingly
			 */
			if (*firstdig < *ean_aux1 && !ean_in1)
				upper = search;
			else
				lower = search;

			step = (upper - lower) / 2;
			search = lower + step;

			/* Initialize stuff again: */
			firstdig = bufI;
			ean_in1 = ean_in2 = false;
			ean_aux1 = TABLE[search][0];
			ean_aux2 = TABLE[search][1];
		}
	} while (step);

	if (step)
	{
		aux1 = bufO;
		aux2 = bufI;
		ean_p = TABLE[search][0];
		while (*ean_p && *aux2)
		{
			if (*ean_p++ != '-')
				*aux1++ = *aux2++;
			else
				*aux1++ = '-';
			ret++;
		}
		*aux1++ = '-';
		*aux1 = *aux2;			/* add a lookahead char */
		return (ret + 1);
	}
	return ret;
}