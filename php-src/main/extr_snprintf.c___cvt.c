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
 scalar_t__ malloc (size_t) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 char* zend_dtoa (double,int,int,int*,int*,char**) ; 
 int /*<<< orphan*/  zend_freedtoa (char*) ; 

__attribute__((used)) static char * __cvt(double value, int ndigit, int *decpt, int *sign, int fmode, int pad) /* {{{ */
{
	register char *s = NULL;
	char *p, *rve, c;
	size_t siz;

	if (ndigit < 0) {
		siz = -ndigit + 1;
	} else {
		siz = ndigit + 1;
	}

	/* __dtoa() doesn't allocate space for 0 so we do it by hand */
	if (value == 0.0) {
		*decpt = 1 - fmode; /* 1 for 'e', 0 for 'f' */
		*sign = 0;
		if ((rve = s = (char *)malloc(ndigit?siz:2)) == NULL) {
			return(NULL);
		}
		*rve++ = '0';
		*rve = '\0';
		if (!ndigit) {
			return(s);
		}
	} else {
		p = zend_dtoa(value, fmode + 2, ndigit, decpt, sign, &rve);
		if (*decpt == 9999) {
			/* Infinity or Nan, convert to inf or nan like printf */
			*decpt = 0;
			c = *p;
			zend_freedtoa(p);
			return strdup((c == 'I' ? "INF" : "NAN"));
		}
		/* Make a local copy and adjust rve to be in terms of s */
		if (pad && fmode) {
			siz += *decpt;
		}
		if ((s = (char *)malloc(siz+1)) == NULL) {
			zend_freedtoa(p);
			return(NULL);
		}
		(void) strlcpy(s, p, siz);
		rve = s + (rve - p);
		zend_freedtoa(p);
	}

	/* Add trailing zeros */
	if (pad) {
		siz -= rve - s;
		while (--siz) {
			*rve++ = '0';
		}
		*rve = '\0';
	}

	return(s);
}