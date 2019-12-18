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
struct TYPE_3__ {scalar_t__ type; } ;
typedef  TYPE_1__ gs_texture_t ;

/* Variables and functions */
 scalar_t__ GS_TEXTURE_2D ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static inline bool is_texture_2d(const gs_texture_t *tex, const char *func)
{
	bool is_tex2d = tex->type == GS_TEXTURE_2D;
	if (!is_tex2d)
		blog(LOG_ERROR, "%s (GL) failed:  Not a 2D texture", func);
	return is_tex2d;
}