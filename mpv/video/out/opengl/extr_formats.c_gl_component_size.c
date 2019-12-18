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
#define  GL_FLOAT 130 
#define  GL_UNSIGNED_BYTE 129 
#define  GL_UNSIGNED_SHORT 128 

int gl_component_size(GLenum type)
{
    switch (type) {
    case GL_UNSIGNED_BYTE:                      return 1;
    case GL_UNSIGNED_SHORT:                     return 2;
    case GL_FLOAT:                              return 4;
    }
    return 0;
}