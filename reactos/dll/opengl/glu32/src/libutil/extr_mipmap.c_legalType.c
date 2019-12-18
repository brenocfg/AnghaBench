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
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
#define  GL_BITMAP 147 
#define  GL_BYTE 146 
 int /*<<< orphan*/  GL_FALSE ; 
#define  GL_FLOAT 145 
#define  GL_INT 144 
#define  GL_SHORT 143 
 int /*<<< orphan*/  GL_TRUE ; 
#define  GL_UNSIGNED_BYTE 142 
#define  GL_UNSIGNED_BYTE_2_3_3_REV 141 
#define  GL_UNSIGNED_BYTE_3_3_2 140 
#define  GL_UNSIGNED_INT 139 
#define  GL_UNSIGNED_INT_10_10_10_2 138 
#define  GL_UNSIGNED_INT_2_10_10_10_REV 137 
#define  GL_UNSIGNED_INT_8_8_8_8 136 
#define  GL_UNSIGNED_INT_8_8_8_8_REV 135 
#define  GL_UNSIGNED_SHORT 134 
#define  GL_UNSIGNED_SHORT_1_5_5_5_REV 133 
#define  GL_UNSIGNED_SHORT_4_4_4_4 132 
#define  GL_UNSIGNED_SHORT_4_4_4_4_REV 131 
#define  GL_UNSIGNED_SHORT_5_5_5_1 130 
#define  GL_UNSIGNED_SHORT_5_6_5 129 
#define  GL_UNSIGNED_SHORT_5_6_5_REV 128 

__attribute__((used)) static GLboolean legalType(GLenum type)
{
    switch(type) {
      case GL_BITMAP:
      case GL_BYTE:
      case GL_UNSIGNED_BYTE:
      case GL_SHORT:
      case GL_UNSIGNED_SHORT:
      case GL_INT:
      case GL_UNSIGNED_INT:
      case GL_FLOAT:
      case GL_UNSIGNED_BYTE_3_3_2:
      case GL_UNSIGNED_BYTE_2_3_3_REV:  
      case GL_UNSIGNED_SHORT_5_6_5:
      case GL_UNSIGNED_SHORT_5_6_5_REV:
      case GL_UNSIGNED_SHORT_4_4_4_4:
      case GL_UNSIGNED_SHORT_4_4_4_4_REV:
      case GL_UNSIGNED_SHORT_5_5_5_1:
      case GL_UNSIGNED_SHORT_1_5_5_5_REV:
      case GL_UNSIGNED_INT_8_8_8_8:
      case GL_UNSIGNED_INT_8_8_8_8_REV:
      case GL_UNSIGNED_INT_10_10_10_2:
      case GL_UNSIGNED_INT_2_10_10_10_REV:
	 return GL_TRUE;
      default:
	return GL_FALSE;
    }
}