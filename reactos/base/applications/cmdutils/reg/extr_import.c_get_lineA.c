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
 char* GetWideString (char*) ; 
 size_t REG_VAL_BUF_SIZE ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 char* heap_xalloc (size_t) ; 
 char* heap_xrealloc (char*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 size_t strlen (char*) ; 
 char* strpbrk (char*,char*) ; 

__attribute__((used)) static WCHAR *get_lineA(FILE *fp)
{
    static WCHAR *lineW;
    static size_t size;
    static char *buf, *next;
    char *line;

    heap_free(lineW);

    if (!fp) goto cleanup;

    if (!size)
    {
        size = REG_VAL_BUF_SIZE;
        buf = heap_xalloc(size);
        *buf = 0;
        next = buf;
    }
    line = next;

    while (next)
    {
        char *p = strpbrk(line, "\r\n");
        if (!p)
        {
            size_t len, count;
            len = strlen(next);
            memmove(buf, next, len + 1);
            if (size - len < 3)
            {
                size *= 2;
                buf = heap_xrealloc(buf, size);
            }
            if (!(count = fread(buf + len, 1, size - len - 1, fp)))
            {
                next = NULL;
                lineW = GetWideString(buf);
                return lineW;
            }
            buf[len + count] = 0;
            next = buf;
            line = buf;
            continue;
        }
        next = p + 1;
        if (*p == '\r' && *(p + 1) == '\n') next++;
        *p = 0;
        lineW = GetWideString(line);
        return lineW;
    }

cleanup:
    lineW = NULL;
    if (size) heap_free(buf);
    size = 0;
    return NULL;
}