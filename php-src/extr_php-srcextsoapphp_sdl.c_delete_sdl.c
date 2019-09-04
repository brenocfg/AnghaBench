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
typedef  TYPE_1__* sdlPtr ;
struct TYPE_3__ {int /*<<< orphan*/  is_persistent; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_sdl_impl (TYPE_1__*) ; 

void delete_sdl(void *handle)
{
	sdlPtr tmp = (sdlPtr)handle;

	if (!tmp->is_persistent) {
		delete_sdl_impl(tmp);
	}
}