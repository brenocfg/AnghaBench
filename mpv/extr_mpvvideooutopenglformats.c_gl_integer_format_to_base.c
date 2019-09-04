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
 int GL_RED ; 
#define  GL_RED_INTEGER 131 
 int GL_RG ; 
 int GL_RGB ; 
 int GL_RGBA ; 
#define  GL_RGBA_INTEGER 130 
#define  GL_RGB_INTEGER 129 
#define  GL_RG_INTEGER 128 

GLenum gl_integer_format_to_base(GLenum format)
{
    switch (format) {
    case GL_RED_INTEGER:        return GL_RED;
    case GL_RG_INTEGER:         return GL_RG;
    case GL_RGB_INTEGER:        return GL_RGB;
    case GL_RGBA_INTEGER:       return GL_RGBA;
    }
    return 0;
}