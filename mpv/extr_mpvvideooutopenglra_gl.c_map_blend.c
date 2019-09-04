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
typedef  enum ra_blend { ____Placeholder_ra_blend } ra_blend ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ONE ; 
 int /*<<< orphan*/  GL_ONE_MINUS_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_ZERO ; 
#define  RA_BLEND_ONE 131 
#define  RA_BLEND_ONE_MINUS_SRC_ALPHA 130 
#define  RA_BLEND_SRC_ALPHA 129 
#define  RA_BLEND_ZERO 128 

__attribute__((used)) static GLenum map_blend(enum ra_blend blend)
{
    switch (blend) {
    case RA_BLEND_ZERO:                 return GL_ZERO;
    case RA_BLEND_ONE:                  return GL_ONE;
    case RA_BLEND_SRC_ALPHA:            return GL_SRC_ALPHA;
    case RA_BLEND_ONE_MINUS_SRC_ALPHA:  return GL_ONE_MINUS_SRC_ALPHA;
    default: return 0;
    }
}