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
typedef  int GLenum ;

/* Variables and functions */
#define  GL_UNSIGNED_INT_2_10_10_10_REV 131 
#define  GL_UNSIGNED_SHORT_5_6_5 130 
#define  GL_UNSIGNED_SHORT_8_8_APPLE 129 
#define  GL_UNSIGNED_SHORT_8_8_REV_APPLE 128 
 int gl_component_size (int) ; 
 int gl_format_components (int) ; 

int gl_bytes_per_pixel(GLenum format, GLenum type)
{
    // Formats with merged components are special.
    switch (type) {
    case GL_UNSIGNED_INT_2_10_10_10_REV:        return 4;
    case GL_UNSIGNED_SHORT_5_6_5:               return 2;
    case GL_UNSIGNED_SHORT_8_8_APPLE:           return 2;
    case GL_UNSIGNED_SHORT_8_8_REV_APPLE:       return 2;
    }

    return gl_component_size(type) * gl_format_components(format);
}