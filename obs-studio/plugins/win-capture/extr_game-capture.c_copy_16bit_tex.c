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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct game_capture {TYPE_1__* global_hook_info; } ;
struct TYPE_2__ {scalar_t__ format; } ;

/* Variables and functions */
 scalar_t__ DXGI_FORMAT_B5G5R5A1_UNORM ; 
 scalar_t__ DXGI_FORMAT_B5G6R5_UNORM ; 
 int /*<<< orphan*/  copy_b5g5r5a1_tex (struct game_capture*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_b5g6r5_tex (struct game_capture*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void copy_16bit_tex(struct game_capture *gc, int cur_texture,
				  uint8_t *data, uint32_t pitch)
{
	if (gc->global_hook_info->format == DXGI_FORMAT_B5G5R5A1_UNORM) {
		copy_b5g5r5a1_tex(gc, cur_texture, data, pitch);

	} else if (gc->global_hook_info->format == DXGI_FORMAT_B5G6R5_UNORM) {
		copy_b5g6r5_tex(gc, cur_texture, data, pitch);
	}
}