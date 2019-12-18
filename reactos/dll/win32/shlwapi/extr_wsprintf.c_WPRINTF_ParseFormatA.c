#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; int width; int precision; void* type; } ;
typedef  TYPE_1__ WPRINTF_FORMAT ;
typedef  char* LPCSTR ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int WPRINTF_I64 ; 
 int WPRINTF_INTPTR ; 
 int WPRINTF_LEFTALIGN ; 
 int WPRINTF_LONG ; 
 int WPRINTF_PREFIX_HEX ; 
 int WPRINTF_SHORT ; 
 int WPRINTF_UPPER_HEX ; 
 int WPRINTF_WIDE ; 
 int WPRINTF_ZEROPAD ; 
 void* WPR_CHAR ; 
 void* WPR_HEXA ; 
 void* WPR_SIGNED ; 
 void* WPR_STRING ; 
 void* WPR_UNKNOWN ; 
 void* WPR_UNSIGNED ; 
 void* WPR_WCHAR ; 
 void* WPR_WSTRING ; 

__attribute__((used)) static INT WPRINTF_ParseFormatA( LPCSTR format, WPRINTF_FORMAT *res )
{
    LPCSTR p = format;

    res->flags = 0;
    res->width = 0;
    res->precision = 0;
    if (*p == '-') { res->flags |= WPRINTF_LEFTALIGN; p++; }
    if (*p == '#') { res->flags |= WPRINTF_PREFIX_HEX; p++; }
    if (*p == '0') { res->flags |= WPRINTF_ZEROPAD; p++; }
    while ((*p >= '0') && (*p <= '9'))  /* width field */
    {
        res->width = res->width * 10 + *p - '0';
        p++;
    }
    if (*p == '.')  /* precision field */
    {
        p++;
        while ((*p >= '0') && (*p <= '9'))
        {
            res->precision = res->precision * 10 + *p - '0';
            p++;
        }
    }
    if (*p == 'l') { res->flags |= WPRINTF_LONG; p++; }
    else if (*p == 'h') { res->flags |= WPRINTF_SHORT; p++; }
    else if (*p == 'w') { res->flags |= WPRINTF_WIDE; p++; }
    else if (*p == 'I')
    {
        if (p[1] == '6' && p[2] == '4') { res->flags |= WPRINTF_I64; p += 3; }
        else if (p[1] == '3' && p[2] == '2') p += 3;
        else { res->flags |= WPRINTF_INTPTR; p++; }
    }
    switch(*p)
    {
    case 'c':
        res->type = (res->flags & WPRINTF_LONG) ? WPR_WCHAR : WPR_CHAR;
        break;
    case 'C':
        res->type = (res->flags & WPRINTF_SHORT) ? WPR_CHAR : WPR_WCHAR;
        break;
    case 'd':
    case 'i':
        res->type = WPR_SIGNED;
        break;
    case 's':
        res->type = (res->flags & (WPRINTF_LONG |WPRINTF_WIDE)) ? WPR_WSTRING : WPR_STRING;
        break;
    case 'S':
        res->type = (res->flags & (WPRINTF_SHORT|WPRINTF_WIDE)) ? WPR_STRING : WPR_WSTRING;
        break;
    case 'u':
        res->type = WPR_UNSIGNED;
        break;
    case 'p':
        res->width = 2 * sizeof(void *);
        res->flags |= WPRINTF_ZEROPAD | WPRINTF_INTPTR;
        /* fall through */
    case 'X':
        res->flags |= WPRINTF_UPPER_HEX;
        /* fall through */
    case 'x':
        res->type = WPR_HEXA;
        break;
    default: /* unknown format char */
        res->type = WPR_UNKNOWN;
        p--;  /* print format as normal char */
        break;
    }
    return (INT)(p - format) + 1;
}