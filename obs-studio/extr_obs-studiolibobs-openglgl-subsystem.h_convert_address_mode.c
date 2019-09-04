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
typedef  enum gs_address_mode { ____Placeholder_gs_address_mode } gs_address_mode ;
typedef  int /*<<< orphan*/  GLint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_CLAMP_TO_BORDER ; 
 int /*<<< orphan*/  GL_CLAMP_TO_EDGE ; 
 int /*<<< orphan*/  GL_MIRRORED_REPEAT ; 
 int /*<<< orphan*/  GL_MIRROR_CLAMP_EXT ; 
 int /*<<< orphan*/  GL_REPEAT ; 
#define  GS_ADDRESS_BORDER 132 
#define  GS_ADDRESS_CLAMP 131 
#define  GS_ADDRESS_MIRROR 130 
#define  GS_ADDRESS_MIRRORONCE 129 
#define  GS_ADDRESS_WRAP 128 

__attribute__((used)) static inline GLint convert_address_mode(enum gs_address_mode mode)
{
	switch (mode) {
	case GS_ADDRESS_WRAP:       return GL_REPEAT;
	case GS_ADDRESS_CLAMP:      return GL_CLAMP_TO_EDGE;
	case GS_ADDRESS_MIRROR:     return GL_MIRRORED_REPEAT;
	case GS_ADDRESS_BORDER:     return GL_CLAMP_TO_BORDER;
	case GS_ADDRESS_MIRRORONCE: return GL_MIRROR_CLAMP_EXT;
	}

	return GL_REPEAT;
}