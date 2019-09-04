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
typedef  int /*<<< orphan*/  uint32_t ;
struct fbo_info {int dummy; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;

/* Variables and functions */
 struct fbo_info* get_fbo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_tex_dimensions (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct fbo_info *get_fbo_by_tex(gs_texture_t *tex)
{
	uint32_t width, height;
	if (!get_tex_dimensions(tex, &width, &height))
		return NULL;

	return get_fbo(tex, width, height);
}