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
struct TYPE_3__ {size_t num; scalar_t__ array; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_free (TYPE_1__) ; 
 TYPE_1__ font_list ; 
 int /*<<< orphan*/  font_path_info_free (scalar_t__) ; 

void free_os_font_list(void)
{
	for (size_t i = 0; i < font_list.num; i++)
		font_path_info_free(font_list.array + i);
	da_free(font_list);
}