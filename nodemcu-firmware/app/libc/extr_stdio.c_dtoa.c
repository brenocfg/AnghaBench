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
typedef  scalar_t__ rtype ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_FCONVERSION ; 
 int MAX_FRACT ; 
 int /*<<< orphan*/  _finite (scalar_t__) ; 
 scalar_t__ _isNan (scalar_t__) ; 
 int cvt (scalar_t__,int,char*,int,char*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

void dtoa (char *dbuf, rtype arg, int fmtch, int width, int prec)
{
    char    buf[MAX_FCONVERSION+1], *cp;
    char    sign;
    int size;

    if( !_finite(arg) ) {
        if( _isNan(arg) )
            strcpy (dbuf, "NaN");
        else if( arg < 0)
            strcpy (dbuf, "-Infinity");
        else
            strcpy (dbuf, "Infinity");
        return;
    }

    if (prec == 0)
        prec = 6;
    else if (prec > MAX_FRACT)
        prec = MAX_FRACT;

    /* leave room for sign at start of buffer */
    cp = buf + 1;

    /*
     * cvt may have to round up before the "start" of
     * its buffer, i.e. ``intf("%.2f", (double)9.999);'';
     * if the first character is still NUL, it did.
     * softsign avoids negative 0 if _double < 0 but
     * no significant digits will be shown.
     */
    *cp = '\0';
    size = cvt (arg, prec, &sign, fmtch, cp, buf + sizeof(buf));
    if (*cp == '\0')
        cp++;

    if (sign)
        *--cp = sign, size++;

    cp[size] = 0;
    memcpy (dbuf, cp, size + 1);
}