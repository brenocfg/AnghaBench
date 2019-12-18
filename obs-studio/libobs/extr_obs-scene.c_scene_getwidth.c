#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  cx; scalar_t__ custom_size; } ;
typedef  TYPE_2__ obs_scene_t ;
struct TYPE_4__ {int /*<<< orphan*/  base_width; } ;
struct TYPE_6__ {TYPE_1__ video; } ;

/* Variables and functions */
 TYPE_3__* obs ; 

__attribute__((used)) static uint32_t scene_getwidth(void *data)
{
	obs_scene_t *scene = data;
	return scene->custom_size ? scene->cx : obs->video.base_width;
}