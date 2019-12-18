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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ICONINFO ;

/* Variables and functions */
 int /*<<< orphan*/ * copy_from_color (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * copy_from_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline uint8_t *cursor_capture_icon_bitmap(ICONINFO *ii, uint32_t *width,
						  uint32_t *height)
{
	uint8_t *output;

	output = copy_from_color(ii, width, height);
	if (!output)
		output = copy_from_mask(ii, width, height);

	return output;
}