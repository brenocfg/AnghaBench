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
 int FALSE ; 
 int TRUE ; 
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ isspace (unsigned char) ; 
 double* powersOf10 ; 

double strtod(const char *string, char **endPtr)
{
    int maxExponent = 511;  /* Largest possible base 10 exponent.  Any
                 * exponent larger than this will already
                 * produce underflow or overflow, so there's
                 * no need to worry about additional digits.
                 */

    int sign, expSign = FALSE;
    double fraction, dblExp, *d;
    register const char *p;
    register int c;
    int exp = 0;        /* Exponent read from "EX" field. */
    int fracExp = 0;        /* Exponent that derives from the fractional
                 * part.  Under normal circumstatnces, it is
                 * the negative of the number of digits in F.
                 * However, if I is very long, the last digits
                 * of I get dropped (otherwise a long I with a
                 * large negative exponent could cause an
                 * unnecessary overflow on I alone).  In this
                 * case, fracExp is incremented one for each
                 * dropped digit. */
    int mantSize;       /* Number of digits in mantissa. */
    int decPt;          /* Number of mantissa digits BEFORE decimal
                 * point. */
    const char *pExp;       /* Temporarily holds location of exponent
                 * in string. */

    /*
     * Strip off leading blanks and check for a sign.
     */

    p = string;
    while (isspace((unsigned char)(*p)))
    {
        p += 1;
    }
    if (*p == '-')
    {
        sign = TRUE;
        p += 1;
    }
    else
    {
        if (*p == '+')
        {
            p += 1;
        }
        sign = FALSE;
    }

    /*
     * Count the number of digits in the mantissa (including the decimal
     * point), and also locate the decimal point.
     */

    decPt = -1;
    for (mantSize = 0; ; mantSize += 1)
    {
        c = *p;
        if (!isdigit(c))
        {
            if ((c != '.') || (decPt >= 0))
            {
                break;
            }
            decPt = mantSize;
        }
        p += 1;
    }

    /*
     * Now suck up the digits in the mantissa.  Use two integers to
     * collect 9 digits each (this is faster than using floating-point).
     * If the mantissa has more than 18 digits, ignore the extras, since
     * they can't affect the value anyway.
     */

    pExp  = p;
    p -= mantSize;
    if (decPt < 0)
    {
        decPt = mantSize;
    }
    else
    {
        mantSize -= 1;          /* One of the digits was the point. */
    }
    if (mantSize > 18)
    {
        fracExp = decPt - 18;
        mantSize = 18;
    }
    else
    {
        fracExp = decPt - mantSize;
    }
    if (mantSize == 0)
    {
        fraction = 0.0;
        p = string;
        goto done;
    }
    else
    {
        int frac1, frac2;
        frac1 = 0;
        for ( ; mantSize > 9; mantSize -= 1)
        {
            c = *p;
            p += 1;
            if (c == '.')
            {
                c = *p;
                p += 1;
            }
            frac1 = 10 * frac1 + (c - '0');
        }
        frac2 = 0;
        for (; mantSize > 0; mantSize -= 1)
        {
            c = *p;
            p += 1;
            if (c == '.')
            {
                c = *p;
                p += 1;
            }
            frac2 = 10 * frac2 + (c - '0');
        }
        fraction = (1.0e9 * frac1) + frac2;
    }

    /*
     * Skim off the exponent.
     */

    p = pExp;
    if ((*p == 'E') || (*p == 'e'))
    {
        p += 1;
        if (*p == '-')
        {
            expSign = TRUE;
            p += 1;
        }
        else
        {
            if (*p == '+')
            {
                p += 1;
            }
            expSign = FALSE;
        }
        if (!isdigit((unsigned char)(*p)))
        {
            p = pExp;
            goto done;
        }
        while (isdigit((unsigned char)(*p)))
        {
            exp = exp * 10 + (*p - '0');
            p += 1;
        }
    }
    if (expSign)
    {
        exp = fracExp - exp;
    }
    else
    {
        exp = fracExp + exp;
    }

    /*
     * Generate a floating-point number that represents the exponent.
     * Do this by processing the exponent one bit at a time to combine
     * many powers of 2 of 10. Then combine the exponent with the
     * fraction.
     */

    if (exp < 0)
    {
        expSign = TRUE;
        exp = -exp;
    }
    else
    {
        expSign = FALSE;
    }
    if (exp > maxExponent)
    {
        exp = maxExponent;
        // errno = ERANGE;
    }
    dblExp = 1.0;
    for (d = powersOf10; exp != 0; exp >>= 1, d += 1)
    {
        if (exp & 01)
        {
            dblExp *= *d;
        }
    }
    if (expSign)
    {
        fraction /= dblExp;
    }
    else
    {
        fraction *= dblExp;
    }

done:
    if (endPtr != NULL)
    {
        *endPtr = (char *) p;
    }

    if (sign)
    {
        return -fraction;
    }
    return fraction;
}