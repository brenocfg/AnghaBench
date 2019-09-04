#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  attribs; int /*<<< orphan*/  label; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ m_obj_settings_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_str_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void obj_setting_free(m_obj_settings_t *item)
{
    talloc_free(item->name);
    talloc_free(item->label);
    free_str_list(&(item->attribs));
}