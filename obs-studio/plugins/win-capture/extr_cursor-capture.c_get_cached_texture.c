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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {size_t num; struct cached_cursor* array; } ;
struct cursor_data {TYPE_1__ cached_textures; } ;
struct cached_cursor {scalar_t__ cx; scalar_t__ cy; int /*<<< orphan*/ * texture; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;

/* Variables and functions */
 int /*<<< orphan*/  GS_BGRA ; 
 int /*<<< orphan*/  GS_DYNAMIC ; 
 int /*<<< orphan*/  da_push_back (TYPE_1__,struct cached_cursor*) ; 
 int /*<<< orphan*/ * gs_texture_create (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static gs_texture_t *get_cached_texture(struct cursor_data *data, uint32_t cx,
					uint32_t cy)
{
	struct cached_cursor cc;

	for (size_t i = 0; i < data->cached_textures.num; i++) {
		struct cached_cursor *pcc = &data->cached_textures.array[i];

		if (pcc->cx == cx && pcc->cy == cy)
			return pcc->texture;
	}

	cc.texture = gs_texture_create(cx, cy, GS_BGRA, 1, NULL, GS_DYNAMIC);
	cc.cx = cx;
	cc.cy = cy;
	da_push_back(data->cached_textures, &cc);
	return cc.texture;
}