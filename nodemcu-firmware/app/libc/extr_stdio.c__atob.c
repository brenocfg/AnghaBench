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
typedef  int u_quad_t ;
typedef  int /*<<< orphan*/  tmp ;

/* Variables and functions */
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static int
_atob (u_quad_t *vp, char *p, int base)
{
    u_quad_t value, v1, v2;
    char *q, tmp[20];
    int digit;

    if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
        base = 16;
        p += 2;
    }

    if (base == 16 && (q = strchr (p, '.')) != 0) {
        if (q - p > sizeof(tmp) - 1)
            return (0);

        strncpy (tmp, p, q - p);
        tmp[q - p] = '\0';
        if (!_atob (&v1, tmp, 16))
            return (0);

        q++;
        if (strchr (q, '.'))
            return (0);

        if (!_atob (&v2, q, 16))
            return (0);
        *vp = (v1 << 16) + v2;
        return (1);
    }

    value = *vp = 0;
    for (; *p; p++) {
        if (*p >= '0' && *p <= '9')
            digit = *p - '0';
        else if (*p >= 'a' && *p <= 'f')
            digit = *p - 'a' + 10;
        else if (*p >= 'A' && *p <= 'F')
            digit = *p - 'A' + 10;
        else
            return (0);

        if (digit >= base)
            return (0);
        value *= base;
        value += digit;
    }
    *vp = value;
    return (1);
}