#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct d3dx_parameter {char* full_name; char* name; int element_count; unsigned int member_count; struct d3dx_parameter* members; TYPE_1__* top_level_param; int /*<<< orphan*/  rb_entry; } ;
struct d3dx9_base_effect {int /*<<< orphan*/  param_tree; } ;
struct TYPE_2__ {unsigned int annotation_count; struct d3dx_parameter* annotations; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  debugstr_a (char*) ; 
 void* heap_alloc (unsigned int) ; 
 scalar_t__ is_top_level_parameter (struct d3dx_parameter*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  wine_rb_put (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_param_to_tree(struct d3dx9_base_effect *base, struct d3dx_parameter *param,
        struct d3dx_parameter *parent, char separator, unsigned int element)
{
    const char *parent_name = parent ? parent->full_name : NULL;
    unsigned int i;

    TRACE("Adding parameter %p (%s - parent %p, element %u) to the rbtree.\n",
            param, debugstr_a(param->name), parent, element);

    if (parent_name)
    {
        unsigned int parent_name_len = strlen(parent_name);
        unsigned int name_len = strlen(param->name);
        unsigned int part_str_len;
        unsigned int len;
        char part_str[16];

        if (separator == '[')
        {
            sprintf(part_str, "[%u]", element);
            part_str_len = strlen(part_str);
            name_len = 0;
        }
        else
        {
            part_str[0] = separator;
            part_str[1] = 0;
            part_str_len = 1;
        }
        len = parent_name_len + part_str_len + name_len + 1;

        if (!(param->full_name = heap_alloc(len)))
        {
            ERR("Out of memory.\n");
            return;
        }

        memcpy(param->full_name, parent_name, parent_name_len);
        memcpy(param->full_name + parent_name_len, part_str, part_str_len);
        memcpy(param->full_name + parent_name_len + part_str_len, param->name, name_len);
        param->full_name[len - 1] = 0;
    }
    else
    {
        unsigned int len = strlen(param->name) + 1;

        if (!(param->full_name = heap_alloc(len)))
        {
            ERR("Out of memory.\n");
            return;
        }

        memcpy(param->full_name, param->name, len);
    }
    TRACE("Full name is %s.\n", param->full_name);
    wine_rb_put(&base->param_tree, param->full_name, &param->rb_entry);

    if (is_top_level_parameter(param))
        for (i = 0; i < param->top_level_param->annotation_count; ++i)
            add_param_to_tree(base, &param->top_level_param->annotations[i], param, '@', 0);

    if (param->element_count)
        for (i = 0; i < param->element_count; ++i)
            add_param_to_tree(base, &param->members[i], param, '[', i);
    else
        for (i = 0; i < param->member_count; ++i)
            add_param_to_tree(base, &param->members[i], param, '.', 0);
}