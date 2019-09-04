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
 int CAL_JEWISH_ADD_ALAFIM ; 
 int CAL_JEWISH_ADD_ALAFIM_GERESH ; 
 int CAL_JEWISH_ADD_GERESHAYIM ; 
 char* alef_bet ; 
 char* estrndup (char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static char *heb_number_to_chars(int n, int fl, char **ret)
{
	char *p, old[18], *endofalafim;

	p = endofalafim = old;
/*
   prevents the option breaking the jewish beliefs, and some other
   critical resources ;)
 */
	if (n > 9999 || n < 1) {
		*ret = NULL;
		return NULL;
	}

/* alafim (thousands) case */
	if (n / 1000) {
		*p = alef_bet[n / 1000];
		p++;

		if (CAL_JEWISH_ADD_ALAFIM_GERESH & fl) {
			*p = '\'';
			p++;
		}
		if (CAL_JEWISH_ADD_ALAFIM & fl) {
			/* Escape sequences of Hebrew characters in ISO-8859-8: אלפים */
			strcpy(p, " \xE0\xEC\xF4\xE9\xED ");
			p += 7;
		}

		endofalafim = p;
		n = n % 1000;
	}

/* tav-tav (tav=400) case */
	while (n >= 400) {
		*p = alef_bet[22];
		p++;
		n -= 400;
	}

/* meot (hundreads) case */
	if (n >= 100) {
		*p = alef_bet[18 + n / 100];
		p++;
		n = n % 100;
	}

/* tet-vav & tet-zain case (special case for 15 and 16) */
	if (n == 15 || n == 16) {
		*p = alef_bet[9];
		p++;
		*p = alef_bet[n - 9];
		p++;
	} else {
/* asarot (tens) case */
		if (n >= 10) {
			*p = alef_bet[9 + n / 10];
			p++;
			n = n % 10;
		}

/* yehidot (ones) case */
		if (n > 0) {
			*p = alef_bet[n];
			p++;
		}
	}

	if (CAL_JEWISH_ADD_GERESHAYIM & fl) {
		switch (p - endofalafim) {
		case 0:
			break;
		case 1:
			*p = '\'';
			p++;
			break;
		default:
			*(p) = *(p - 1);
			*(p - 1) = '"';
			p++;
		}
	}

	*p = '\0';
	*ret = estrndup(old, (p - old) + 1);
	p = *ret;
	return p;
}