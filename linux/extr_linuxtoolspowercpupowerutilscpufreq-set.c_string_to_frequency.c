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
struct freq_units {scalar_t__* str_unit; int power_of_ten; } ;

/* Variables and functions */
 int NORM_FREQ_LEN ; 
 unsigned long ULONG_MAX ; 
 struct freq_units* def_units ; 
 scalar_t__ errno ; 
 scalar_t__ isdigit (char const) ; 
 unsigned long strtoul (char*,char**,int) ; 
 scalar_t__ tolower (char const) ; 

__attribute__((used)) static unsigned long string_to_frequency(const char *str)
{
	char normalized[NORM_FREQ_LEN];
	const struct freq_units *unit;
	const char *scan;
	char *end;
	unsigned long freq;
	int power = 0, match_count = 0, i, cp, pad;

	while (*str == '0')
		str++;

	for (scan = str; isdigit(*scan) || *scan == '.'; scan++) {
		if (*scan == '.' && match_count == 0)
			match_count = 1;
		else if (*scan == '.' && match_count == 1)
			return 0;
	}

	if (*scan) {
		match_count = 0;
		for (unit = def_units; unit->str_unit; unit++) {
			for (i = 0;
			     scan[i] && tolower(scan[i]) == unit->str_unit[i];
			     ++i)
				continue;
			if (scan[i])
				continue;
			match_count++;
			power = unit->power_of_ten;
		}
		if (match_count != 1)
			return 0;
	}

	/* count the number of digits to be copied */
	for (cp = 0; isdigit(str[cp]); cp++)
		continue;

	if (str[cp] == '.') {
		while (power > -1 && isdigit(str[cp+1]))
			cp++, power--;
	}
	if (power >= -1)	/* not enough => pad */
		pad = power + 1;
	else			/* to much => strip */
		pad = 0, cp += power + 1;
	/* check bounds */
	if (cp <= 0 || cp + pad > NORM_FREQ_LEN - 1)
		return 0;

	/* copy digits */
	for (i = 0; i < cp; i++, str++) {
		if (*str == '.')
			str++;
		normalized[i] = *str;
	}
	/* and pad */
	for (; i < cp + pad; i++)
		normalized[i] = '0';

	/* round up, down ? */
	match_count = (normalized[i-1] >= '5');
	/* and drop the decimal part */
	normalized[i-1] = 0; /* cp > 0 && pad >= 0 ==> i > 0 */

	/* final conversion (and applying rounding) */
	errno = 0;
	freq = strtoul(normalized, &end, 10);
	if (errno)
		return 0;
	else {
		if (match_count && freq != ULONG_MAX)
			freq++;
		return freq;
	}
}