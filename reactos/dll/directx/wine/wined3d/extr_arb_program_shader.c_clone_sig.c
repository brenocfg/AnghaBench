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
struct wined3d_shader_signature {unsigned int element_count; TYPE_1__* elements; } ;
struct TYPE_2__ {char* semantic_name; } ;

/* Variables and functions */
 char* heap_alloc (scalar_t__) ; 
 TYPE_1__* heap_calloc (unsigned int,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void clone_sig(struct wined3d_shader_signature *new, const struct wined3d_shader_signature *sig)
{
    unsigned int i;
    char *name;

    new->element_count = sig->element_count;
    new->elements = heap_calloc(new->element_count, sizeof(*new->elements));
    for (i = 0; i < sig->element_count; ++i)
    {
        new->elements[i] = sig->elements[i];

        if (!new->elements[i].semantic_name)
            continue;

        /* Clone the semantic string */
        name = heap_alloc(strlen(sig->elements[i].semantic_name) + 1);
        strcpy(name, sig->elements[i].semantic_name);
        new->elements[i].semantic_name = name;
    }
}