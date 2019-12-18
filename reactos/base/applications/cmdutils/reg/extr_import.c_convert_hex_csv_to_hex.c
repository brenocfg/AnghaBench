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
struct parser {int data_size; void* backslash; scalar_t__ data; } ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  void* BOOL ;

/* Variables and functions */
 void* FALSE ; 
 void* TRUE ; 
 scalar_t__ heap_xrealloc (scalar_t__,size_t) ; 
 int lstrlenW (char*) ; 
 unsigned long strtoulW (char*,char**,int) ; 

__attribute__((used)) static BOOL convert_hex_csv_to_hex(struct parser *parser, WCHAR **str)
{
    size_t size;
    BYTE *d;
    WCHAR *s;

    parser->backslash = FALSE;

    /* The worst case is 1 digit + 1 comma per byte */
    size = ((lstrlenW(*str) + 1) / 2) + parser->data_size;
    parser->data = heap_xrealloc(parser->data, size);

    s = *str;
    d = (BYTE *)parser->data + parser->data_size;

    while (*s)
    {
        WCHAR *end;
        unsigned long wc;

        wc = strtoulW(s, &end, 16);
        if (wc > 0xff) return FALSE;

        if (s == end && wc == 0)
        {
            while (*end == ' ' || *end == '\t') end++;
            if (*end == '\\')
            {
                parser->backslash = TRUE;
                *str = end + 1;
                return TRUE;
            }
            else if (*end == ';')
                return TRUE;
            return FALSE;
        }

        *d++ = wc;
        parser->data_size++;

        if (*end && *end != ',')
        {
            while (*end == ' ' || *end == '\t') end++;
            if (*end && *end != ';') return FALSE;
            return TRUE;
        }

        if (*end) end++;
        s = end;
    }

    return TRUE;
}