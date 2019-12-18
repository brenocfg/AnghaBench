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
 int /*<<< orphan*/  GetProcessHeap () ; 
 char** HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 char** HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**,unsigned int) ; 
 unsigned int INITIAL_CONST_NAMES_SIZE ; 
 char* next_valid_constant_name (char**) ; 

__attribute__((used)) static const char **parse_skip_constants_string(char *skip_constants_string, unsigned int *names_count)
{
    const char **names, **new_alloc;
    const char *name;
    char *s;
    unsigned int size = INITIAL_CONST_NAMES_SIZE;

    names = HeapAlloc(GetProcessHeap(), 0, sizeof(*names) * size);
    if (!names)
        return NULL;

    *names_count = 0;
    s = skip_constants_string;
    while ((name = next_valid_constant_name(&s)))
    {
        if (*names_count == size)
        {
            size *= 2;
            new_alloc = HeapReAlloc(GetProcessHeap(), 0, names, sizeof(*names) * size);
            if (!new_alloc)
            {
                HeapFree(GetProcessHeap(), 0, names);
                return NULL;
            }
            names = new_alloc;
        }
        names[(*names_count)++] = name;
    }
    new_alloc = HeapReAlloc(GetProcessHeap(), 0, names, *names_count * sizeof(*names));
    if (!new_alloc)
        return names;
    return new_alloc;
}