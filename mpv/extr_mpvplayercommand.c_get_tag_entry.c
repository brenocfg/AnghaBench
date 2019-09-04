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
struct mp_tags {int /*<<< orphan*/ * values; int /*<<< orphan*/ * keys; } ;
struct m_sub_property {char* member_0; int /*<<< orphan*/  member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUB_PROP_STR (int /*<<< orphan*/ ) ; 
 int m_property_read_sub (struct m_sub_property*,int,void*) ; 

__attribute__((used)) static int get_tag_entry(int item, int action, void *arg, void *ctx)
{
    struct mp_tags *tags = ctx;

    struct m_sub_property props[] = {
        {"key",     SUB_PROP_STR(tags->keys[item])},
        {"value",   SUB_PROP_STR(tags->values[item])},
        {0}
    };

    return m_property_read_sub(props, action, arg);
}