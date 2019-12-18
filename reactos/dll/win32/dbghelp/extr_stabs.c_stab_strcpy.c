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
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ isdigit (char) ; 

__attribute__((used)) static void stab_strcpy(char* dest, int sz, const char* source)
{
    char*       ptr = dest;
    /*
     * A strcpy routine that stops when we hit the ':' character.
     * Faster than copying the whole thing, and then nuking the
     * ':'.
     * Takes also care of (valid) a::b constructs
     */
    while (*source != '\0')
    {
        if (source[0] != ':' && sz-- > 0) *ptr++ = *source++;
        else if (source[1] == ':' && (sz -= 2) > 0)
        {
            *ptr++ = *source++;
            *ptr++ = *source++;
        }
        else break;
    }
    *ptr-- = '\0';
    /* GCC emits, in some cases, a .<digit>+ suffix.
     * This is used for static variable inside functions, so
     * that we can have several such variables with same name in
     * the same compilation unit
     * We simply ignore that suffix when present (we also get rid
     * of it in ELF symtab parsing)
     */
    if (ptr >= dest && isdigit(*ptr))
    {
        while (ptr > dest && isdigit(*ptr)) ptr--;
        if (*ptr == '.') *ptr = '\0';
    }
    assert(sz > 0);
}