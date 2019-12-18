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
typedef  double rtype ;

/* Variables and functions */
 int /*<<< orphan*/  ALTERNATE_FORM ; 
 int /*<<< orphan*/  TESTFLAG (int /*<<< orphan*/ ) ; 
 char* c_round (double,int*,char*,char*,char,char*) ; 
 char* exponent (char*,int,int) ; 
 double modf (double,double*) ; 
 void* to_char (int) ; 

__attribute__((used)) static int
cvt(rtype number, int prec, char *signp, int fmtch, char *startp, char *endp)
{
    register char *p, *t;
    register double fract;
    double integer, tmp;
    int dotrim, expcnt, gformat;

    dotrim = expcnt = gformat = 0;
    if (number < 0) {
        number = -number;
        *signp = '-';
    } else
        *signp = 0;

    fract = modf(number, &integer);

    /* get an extra slot for rounding. */
    t = ++startp;

    /*
     * get integer portion of number; put into the end of the buffer; the
     * .01 is added for modf(356.0 / 10, &integer) returning .59999999...
     */
    for (p = endp - 1; integer; ++expcnt) {
        tmp = modf(integer / 10, &integer);
        *p-- = to_char((int)((tmp + .01) * 10));
    }
    switch (fmtch) {
    case 'f':
        /* reverse integer into beginning of buffer */
        if (expcnt)
            for (; ++p < endp; *t++ = *p);
        else
            *t++ = '0';
        /*
         * if precision required or alternate flag set, add in a
         * decimal point.
         */
        if (prec || TESTFLAG(ALTERNATE_FORM))
            *t++ = '.';
        /* if requires more precision and some fraction left */
        if (fract) {
            if (prec)
                do {
                    fract = modf(fract * 10, &tmp);
                    *t++ = to_char((int)tmp);
                } while (--prec && fract);
            if (fract)
                startp = c_round(fract, (int *)NULL, startp,
                    t - 1, (char)0, signp);
        }
        for (; prec--; *t++ = '0');
        break;
    case 'e':
    case 'E':
eformat:    if (expcnt) {
            *t++ = *++p;
            if (prec || TESTFLAG(ALTERNATE_FORM))
                *t++ = '.';
            /* if requires more precision and some integer left */
            for (; prec && ++p < endp; --prec)
                *t++ = *p;
            /*
             * if done precision and more of the integer component,
             * round using it; adjust fract so we don't re-round
             * later.
             */
            if (!prec && ++p < endp) {
                fract = 0;
                startp = c_round((double)0, &expcnt, startp,
                    t - 1, *p, signp);
            }
            /* adjust expcnt for digit in front of decimal */
            --expcnt;
        }
        /* until first fractional digit, decrement exponent */
        else if (fract) {
            /* adjust expcnt for digit in front of decimal */
            for (expcnt = -1;; --expcnt) {
                fract = modf(fract * 10, &tmp);
                if (tmp)
                    break;
            }
            *t++ = to_char((int)tmp);
            if (prec || TESTFLAG(ALTERNATE_FORM))
                *t++ = '.';
        }
        else {
            *t++ = '0';
            if (prec || TESTFLAG(ALTERNATE_FORM))
                *t++ = '.';
        }
        /* if requires more precision and some fraction left */
        if (fract) {
            if (prec)
                do {
                    fract = modf(fract * 10, &tmp);
                    *t++ = to_char((int)tmp);
                } while (--prec && fract);
            if (fract)
                startp = c_round(fract, &expcnt, startp,
                    t - 1, (char)0, signp);
        }
        /* if requires more precision */
        for (; prec--; *t++ = '0');

        /* unless alternate flag, trim any g/G format trailing 0's */
        if (gformat && !TESTFLAG(ALTERNATE_FORM)) {
            while (t > startp && *--t == '0');
            if (*t == '.')
                --t;
            ++t;
        }
        t = exponent(t, expcnt, fmtch);
        break;
    case 'g':
    case 'G':
        /* a precision of 0 is treated as a precision of 1. */
        if (!prec)
            ++prec;
        /*
         * ``The style used depends on the value converted; style e
         * will be used only if the exponent resulting from the
         * conversion is less than -4 or greater than the precision.''
         *  -- ANSI X3J11
         */
        if (expcnt > prec || (!expcnt && fract && fract < .0001)) {
            /*
             * g/G format counts "significant digits, not digits of
             * precision; for the e/E format, this just causes an
             * off-by-one problem, i.e. g/G considers the digit
             * before the decimal point significant and e/E doesn't
             * count it as precision.
             */
            --prec;
            fmtch -= 2;     /* G->E, g->e */
            gformat = 1;
            goto eformat;
        }
        /*
         * reverse integer into beginning of buffer,
         * note, decrement precision
         */
        if (expcnt)
            for (; ++p < endp; *t++ = *p, --prec);
        else
            *t++ = '0';
        /*
         * if precision required or alternate flag set, add in a
         * decimal point.  If no digits yet, add in leading 0.
         */
        if (prec || TESTFLAG(ALTERNATE_FORM)) {
            dotrim = 1;
            *t++ = '.';
        }
        else
            dotrim = 0;
        /* if requires more precision and some fraction left */
        if (fract) {
            if (prec) {
                    do {
                    fract = modf(fract * 10, &tmp);
                    *t++ = to_char((int)tmp);
                } while(!tmp && !expcnt);
                while (--prec && fract) {
                    fract = modf(fract * 10, &tmp);
                    *t++ = to_char((int)tmp);
                }
            }
            if (fract)
                startp = c_round(fract, (int *)NULL, startp,
                    t - 1, (char)0, signp);
        }
        /* alternate format, adds 0's for precision, else trim 0's */
        if (TESTFLAG(ALTERNATE_FORM))
            for (; prec--; *t++ = '0');
        else if (dotrim) {
            while (t > startp && *--t == '0');
            if (*t != '.')
                ++t;
        }
    }
    return (t - startp);
}