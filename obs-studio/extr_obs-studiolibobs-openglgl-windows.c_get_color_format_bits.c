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
typedef  enum gs_color_format { ____Placeholder_gs_color_format } gs_color_format ;

/* Variables and functions */
#define  GS_RGBA 128 

__attribute__((used)) static inline int get_color_format_bits(enum gs_color_format format)
{
	switch ((uint32_t)format) {
	case GS_RGBA:
		return 32;
	default:
		return 0;
	}
}