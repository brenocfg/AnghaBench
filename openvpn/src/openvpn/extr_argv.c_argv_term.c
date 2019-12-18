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
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  check_malloc_return (char*) ; 
 int /*<<< orphan*/  isspace (int const) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

__attribute__((used)) static char *
argv_term(const char **f)
{
    const char *p = *f;
    const char *term = NULL;
    size_t termlen = 0;

    if (*p == '\0')
    {
        return NULL;
    }

    while (true)
    {
        const int c = *p;
        if (c == '\0')
        {
            break;
        }
        if (term)
        {
            if (!isspace(c))
            {
                ++termlen;
            }
            else
            {
                break;
            }
        }
        else
        {
            if (!isspace(c))
            {
                term = p;
                termlen = 1;
            }
        }
        ++p;
    }
    *f = p;

    if (term)
    {
        char *ret;
        ASSERT(termlen > 0);
        ret = malloc(termlen + 1);
        check_malloc_return(ret);
        memcpy(ret, term, termlen);
        ret[termlen] = '\0';
        return ret;
    }
    else
    {
        return NULL;
    }
}