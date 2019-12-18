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
struct vec4 {int dummy; } ;
struct matrix4 {struct vec4 y; struct vec4 x; struct vec4 t; struct vec4 z; } ;
struct TYPE_6__ {float x; float y; } ;
struct TYPE_7__ {scalar_t__ rot; TYPE_1__ scale; int /*<<< orphan*/  pos; int /*<<< orphan*/  draw_transform; } ;
typedef  TYPE_2__ obs_sceneitem_t ;

/* Variables and functions */
 int /*<<< orphan*/  matrix4_inv (struct matrix4*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  matrix4_mul (struct matrix4*,struct matrix4*,struct matrix4*) ; 
 int /*<<< orphan*/  transform_val (int /*<<< orphan*/ *,struct matrix4*) ; 
 int /*<<< orphan*/  update_item_transform (TYPE_2__*,int) ; 
 float vec4_len (struct vec4*) ; 
 int /*<<< orphan*/  vec4_set (struct vec4*,float,float,float,float) ; 

__attribute__((used)) static void apply_group_transform(obs_sceneitem_t *item, obs_sceneitem_t *group)
{
	struct matrix4 transform;
	struct matrix4 mat;
	struct vec4 x_base;

	vec4_set(&x_base, 1.0f, 0.0f, 0.0f, 0.0f);

	matrix4_inv(&transform, &group->draw_transform);

	transform_val(&item->pos, &transform);
	vec4_set(&transform.t, 0.0f, 0.0f, 0.0f, 1.0f);

	vec4_set(&mat.x, item->scale.x, 0.0f, 0.0f, 0.0f);
	vec4_set(&mat.y, 0.0f, item->scale.y, 0.0f, 0.0f);
	vec4_set(&mat.z, 0.0f, 0.0f, 1.0f, 0.0f);
	vec4_set(&mat.t, 0.0f, 0.0f, 0.0f, 1.0f);
	matrix4_mul(&mat, &mat, &transform);

	item->scale.x =
		vec4_len(&mat.x) * (item->scale.x > 0.0f ? 1.0f : -1.0f);
	item->scale.y =
		vec4_len(&mat.y) * (item->scale.y > 0.0f ? 1.0f : -1.0f);
	item->rot -= group->rot;

	update_item_transform(item, false);
}