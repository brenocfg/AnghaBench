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
struct dc_capture {int /*<<< orphan*/  texture; int /*<<< orphan*/ * hdc; scalar_t__ compatibility; int /*<<< orphan*/  valid; } ;
typedef  int /*<<< orphan*/ * HDC ;

/* Variables and functions */
 int /*<<< orphan*/ * gs_texture_get_dc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline HDC dc_capture_get_dc(struct dc_capture *capture)
{
	if (!capture->valid)
		return NULL;

	if (capture->compatibility)
		return capture->hdc;
	else
		return gs_texture_get_dc(capture->texture);
}