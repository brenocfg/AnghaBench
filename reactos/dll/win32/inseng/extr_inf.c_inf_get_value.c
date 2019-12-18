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
struct inf_value {int /*<<< orphan*/  key; } ;
struct inf_section {int dummy; } ;

/* Variables and functions */
 scalar_t__ inf_section_next_value (struct inf_section*,struct inf_value**) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 

struct inf_value *inf_get_value(struct inf_section *sec, const char *key)
{
    struct inf_value *value = NULL;

    while (inf_section_next_value(sec, &value))
    {
        if (!strcasecmp(value->key, key))
            return value;
    }

    return NULL;
}