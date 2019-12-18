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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int hex_to_int (char) ; 
 int /*<<< orphan*/  iswdigit (char) ; 

BOOL unescape(WCHAR *str, size_t *len)
{
    WCHAR *pd, *p, c, *end = str + *len;
    int i;

    pd = p = str;
    while(p < end) {
        if(*p != '\\') {
            *pd++ = *p++;
            continue;
        }

        if(++p == end)
            return FALSE;

        switch(*p) {
        case '\'':
        case '\"':
        case '\\':
            c = *p;
            break;
        case 'b':
            c = '\b';
            break;
        case 't':
            c = '\t';
            break;
        case 'n':
            c = '\n';
            break;
        case 'f':
            c = '\f';
            break;
        case 'r':
            c = '\r';
            break;
        case 'x':
            if(p + 2 >= end)
                return FALSE;
            i = hex_to_int(*++p);
            if(i == -1)
                return FALSE;
            c = i << 4;

            i = hex_to_int(*++p);
            if(i == -1)
                return FALSE;
            c += i;
            break;
        case 'u':
            if(p + 4 >= end)
                return FALSE;
            i = hex_to_int(*++p);
            if(i == -1)
                return FALSE;
            c = i << 12;

            i = hex_to_int(*++p);
            if(i == -1)
                return FALSE;
            c += i << 8;

            i = hex_to_int(*++p);
            if(i == -1)
                return FALSE;
            c += i << 4;

            i = hex_to_int(*++p);
            if(i == -1)
                return FALSE;
            c += i;
            break;
        default:
            if(iswdigit(*p)) {
                c = *p++ - '0';
                if(p < end && iswdigit(*p)) {
                    c = c*8 + (*p++ - '0');
                    if(p < end && iswdigit(*p))
                        c = c*8 + (*p++ - '0');
                }
                p--;
            }
            else
                c = *p;
        }

        *pd++ = c;
        p++;
    }

    *len = pd - str;
    return TRUE;
}