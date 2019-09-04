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
#define  FMT_CENTER 131 
#define  FMT_LJUST 130 
#define  FMT_RJUST 129 
#define  FMT_RJUST0 128 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strichr (char*,char) ; 
 int strlen (char*) ; 

void
str_fmt(char *p, int size, int fmt)
{
    int n, m, len;

    len = strlen (p);
    switch (fmt) {
    case FMT_RJUST:
        for (n = size - len; n > 0; n--)
            strichr (p, ' ');
        break;
    case FMT_LJUST:
        for (m = size - len; m > 0; m--)
            strcat (p, " ");
        break;
    case FMT_RJUST0:
        for (n = size - len; n > 0; n--)
            strichr (p, '0');
        break;
    case FMT_CENTER:
        m = (size - len) / 2;
        n = size - (len + m);
        for (; m > 0; m--)
            strcat (p, " ");
        for (; n > 0; n--)
            strichr (p, ' ');
        break;
    }
}