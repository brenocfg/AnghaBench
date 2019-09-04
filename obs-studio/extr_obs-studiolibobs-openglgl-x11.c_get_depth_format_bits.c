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
typedef  enum gs_zstencil_format { ____Placeholder_gs_zstencil_format } gs_zstencil_format ;

/* Variables and functions */
#define  GS_Z16 129 
#define  GS_Z24_S8 128 

__attribute__((used)) static inline int get_depth_format_bits(enum gs_zstencil_format zsformat)
{
	switch ((uint32_t)zsformat) {
	case GS_Z16:
		return 16;
	case GS_Z24_S8:
		return 24;
	default:
		return 0;
	}
}