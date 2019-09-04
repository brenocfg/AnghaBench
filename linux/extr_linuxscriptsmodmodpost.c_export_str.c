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
typedef  enum export { ____Placeholder_export } export ;
struct TYPE_2__ {char const* str; } ;

/* Variables and functions */
 TYPE_1__* export_list ; 

__attribute__((used)) static const char *export_str(enum export ex)
{
	return export_list[ex].str;
}