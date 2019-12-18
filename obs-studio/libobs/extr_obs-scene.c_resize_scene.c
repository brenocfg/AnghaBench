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
struct vec2 {int dummy; } ;
typedef  int /*<<< orphan*/  obs_scene_t ;

/* Variables and functions */
 int /*<<< orphan*/  resize_scene_base (int /*<<< orphan*/ *,struct vec2*,struct vec2*,struct vec2*) ; 

__attribute__((used)) static void resize_scene(obs_scene_t *scene)
{
	struct vec2 minv;
	struct vec2 maxv;
	struct vec2 scale;
	resize_scene_base(scene, &minv, &maxv, &scale);
}