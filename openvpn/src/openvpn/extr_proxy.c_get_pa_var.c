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
typedef  int /*<<< orphan*/  v ;
struct gc_arena {int dummy; } ;
typedef  int /*<<< orphan*/  k ;

/* Variables and functions */
 int get_key_value (char const*,char*,char*,int,int,char const**) ; 
 scalar_t__ isspace (char const) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char* string_alloc (char*,struct gc_arena*) ; 

__attribute__((used)) static char *
get_pa_var(const char *key, const char *pa, struct gc_arena *gc)
{
    char k[64];
    char v[256];
    const char *content = pa;

    while (true)
    {
        const int status = get_key_value(content, k, v, sizeof(k), sizeof(v), &content);
        if (status)
        {
            if (!strcmp(key, k))
            {
                return string_alloc(v, gc);
            }
        }
        else
        {
            return NULL;
        }

        /* advance to start of next key */
        if (*content == ',')
        {
            ++content;
        }
        while (*content && isspace(*content))
        {
            ++content;
        }
    }
}