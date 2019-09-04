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
typedef  int /*<<< orphan*/  m_obj_settings_t ;

/* Variables and functions */
 int /*<<< orphan*/  bstr0 (char const*) ; 
 int obj_settings_list_find_by_label (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int obj_settings_list_find_by_label0(m_obj_settings_t *obj_list,
                                            const char *label)
{
    return obj_settings_list_find_by_label(obj_list, bstr0(label));
}