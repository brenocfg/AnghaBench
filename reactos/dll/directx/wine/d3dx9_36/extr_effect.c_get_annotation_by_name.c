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
struct d3dx_parameter {int /*<<< orphan*/  name; } ;
struct d3dx9_base_effect {int dummy; } ;
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,char const) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  debugstr_a (char const*) ; 
 struct d3dx_parameter* get_parameter_by_name (struct d3dx9_base_effect*,struct d3dx_parameter*,char const*) ; 
 struct d3dx_parameter* get_parameter_element_by_name (struct d3dx9_base_effect*,struct d3dx_parameter*,char const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int strcspn (char const*,char*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static struct d3dx_parameter *get_annotation_by_name(struct d3dx9_base_effect *base,
        unsigned int count, struct d3dx_parameter *annotations, const char *name)
{
    UINT i, length;
    struct d3dx_parameter *temp_parameter;
    const char *part;

    TRACE("count %u, annotations %p, name %s\n", count, annotations, debugstr_a(name));

    if (!name || !*name) return NULL;

    length = strcspn( name, "[.@" );
    part = name + length;

    for (i = 0; i < count; ++i)
    {
        temp_parameter = &annotations[i];

        if (!strcmp(temp_parameter->name, name))
        {
            TRACE("Returning annotation %p\n", temp_parameter);
            return temp_parameter;
        }
        else if (strlen(temp_parameter->name) == length && !strncmp(temp_parameter->name, name, length))
        {
            switch (*part++)
            {
                case '.':
                    return get_parameter_by_name(base, temp_parameter, part);

                case '[':
                    return get_parameter_element_by_name(base, temp_parameter, part);

                default:
                    FIXME("Unhandled case \"%c\"\n", *--part);
                    break;
            }
        }
    }

    TRACE("Annotation not found\n");
    return NULL;
}