#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  label; scalar_t__ name; } ;
typedef  TYPE_1__ m_obj_settings_t ;
struct TYPE_7__ {scalar_t__ len; } ;
typedef  TYPE_2__ bstr ;

/* Variables and functions */
 scalar_t__ bstr_equals0 (TYPE_2__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int obj_settings_list_find_by_label(m_obj_settings_t *obj_list,
                                           bstr label)
{
    for (int n = 0; obj_list && obj_list[n].name; n++) {
        if (label.len && bstr_equals0(label, obj_list[n].label))
            return n;
    }
    return -1;
}