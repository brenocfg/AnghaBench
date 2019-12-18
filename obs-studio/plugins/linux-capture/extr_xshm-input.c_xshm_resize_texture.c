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
struct xshm_data {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ texture; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_BGRA ; 
 int /*<<< orphan*/  GS_DYNAMIC ; 
 scalar_t__ gs_texture_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_texture_destroy (scalar_t__) ; 

__attribute__((used)) static inline void xshm_resize_texture(struct xshm_data *data)
{
	if (data->texture)
		gs_texture_destroy(data->texture);
	data->texture = gs_texture_create(data->width, data->height, GS_BGRA, 1,
					  NULL, GS_DYNAMIC);
}