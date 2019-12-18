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
typedef  int /*<<< orphan*/  ltW ;
typedef  int /*<<< orphan*/  gtW ;
typedef  int /*<<< orphan*/  escape_mode ;
typedef  int /*<<< orphan*/  equotW ;
typedef  int /*<<< orphan*/  ampW ;
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char const*) ; 
 int /*<<< orphan*/  EscapeValue ; 
 char* heap_alloc (int) ; 
 char* heap_realloc (char*,int) ; 
 int max (int,int const) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static WCHAR *get_escaped_string(const WCHAR *str, escape_mode mode, int *len)
{
    static const WCHAR ltW[]    = {'&','l','t',';'};
    static const WCHAR ampW[]   = {'&','a','m','p',';'};
    static const WCHAR equotW[] = {'&','q','u','o','t',';'};
    static const WCHAR gtW[]    = {'&','g','t',';'};

    const int default_alloc = 100;
    const int grow_thresh = 10;
    int p = *len, conv_len;
    WCHAR *ptr, *ret;

    /* default buffer size to something if length is unknown */
    conv_len = max(2**len, default_alloc);
    ptr = ret = heap_alloc(conv_len*sizeof(WCHAR));

    while (p)
    {
        if (ptr - ret > conv_len - grow_thresh)
        {
            int written = ptr - ret;
            conv_len *= 2;
            ptr = ret = heap_realloc(ret, conv_len*sizeof(WCHAR));
            ptr += written;
        }

        switch (*str)
        {
        case '<':
            memcpy(ptr, ltW, sizeof(ltW));
            ptr += ARRAY_SIZE(ltW);
            break;
        case '&':
            memcpy(ptr, ampW, sizeof(ampW));
            ptr += ARRAY_SIZE(ampW);
            break;
        case '>':
            memcpy(ptr, gtW, sizeof(gtW));
            ptr += ARRAY_SIZE(gtW);
            break;
        case '"':
            if (mode == EscapeValue)
            {
                memcpy(ptr, equotW, sizeof(equotW));
                ptr += ARRAY_SIZE(equotW);
                break;
            }
            /* fallthrough for text mode */
        default:
            *ptr++ = *str;
            break;
        }

        str++;
        p--;
    }

    *len = ptr-ret;
    *++ptr = 0;

    return ret;
}