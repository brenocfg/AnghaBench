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
struct mp_log {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 TYPE_1__* key_names ; 
 int /*<<< orphan*/  mp_info (struct mp_log*,char*,...) ; 

void mp_print_key_list(struct mp_log *out)
{
    mp_info(out, "\n");
    for (int i = 0; key_names[i].name != NULL; i++)
        mp_info(out, "%s\n", key_names[i].name);
}