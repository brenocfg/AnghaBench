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
struct TYPE_2__ {scalar_t__ obj_type; } ;
union handle_word {TYPE_1__ h; int /*<<< orphan*/  w; } ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */

char hpi_handle_object(const u32 handle)
{
	union handle_word uhandle;
	uhandle.w = handle;
	return (char)uhandle.h.obj_type;
}