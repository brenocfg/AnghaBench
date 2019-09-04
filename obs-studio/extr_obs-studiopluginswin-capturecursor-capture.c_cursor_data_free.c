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
struct TYPE_2__ {size_t num; struct cached_cursor* array; } ;
struct cursor_data {TYPE_1__ cached_textures; } ;
struct cached_cursor {int /*<<< orphan*/  texture; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_free (TYPE_1__) ; 
 int /*<<< orphan*/  gs_texture_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cursor_data*,int /*<<< orphan*/ ,int) ; 

void cursor_data_free(struct cursor_data *data)
{
	for (size_t i = 0; i < data->cached_textures.num; i++) {
		struct cached_cursor *pcc = &data->cached_textures.array[i];
		gs_texture_destroy(pcc->texture);
	}
	da_free(data->cached_textures);
	memset(data, 0, sizeof(*data));
}