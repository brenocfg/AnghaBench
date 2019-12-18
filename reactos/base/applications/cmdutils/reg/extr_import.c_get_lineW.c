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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t REG_VAL_BUF_SIZE ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 char* heap_xalloc (size_t) ; 
 char* heap_xrealloc (char*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 size_t strlenW (char*) ; 
 char* strpbrkW (char*,char const*) ; 

__attribute__((used)) static WCHAR *get_lineW(FILE *fp)
{
    static size_t size;
    static WCHAR *buf, *next;
    WCHAR *line;

    if (!fp) goto cleanup;

    if (!size)
    {
        size = REG_VAL_BUF_SIZE;
        buf = heap_xalloc(size * sizeof(WCHAR));
        *buf = 0;
        next = buf;
    }
    line = next;

    while (next)
    {
        static const WCHAR line_endings[] = {'\r','\n',0};
        WCHAR *p = strpbrkW(line, line_endings);
        if (!p)
        {
            size_t len, count;
            len = strlenW(next);
            memmove(buf, next, (len + 1) * sizeof(WCHAR));
            if (size - len < 3)
            {
                size *= 2;
                buf = heap_xrealloc(buf, size * sizeof(WCHAR));
            }
            if (!(count = fread(buf + len, sizeof(WCHAR), size - len - 1, fp)))
            {
                next = NULL;
                return buf;
            }
            buf[len + count] = 0;
            next = buf;
            line = buf;
            continue;
        }
        next = p + 1;
        if (*p == '\r' && *(p + 1) == '\n') next++;
        *p = 0;
        return line;
    }

cleanup:
    if (size) heap_free(buf);
    size = 0;
    return NULL;
}