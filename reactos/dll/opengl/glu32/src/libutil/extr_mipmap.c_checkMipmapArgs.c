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
typedef  scalar_t__ GLenum ;

/* Variables and functions */
 int GLU_INVALID_ENUM ; 
 int GLU_INVALID_OPERATION ; 
 scalar_t__ GL_STENCIL_INDEX ; 
 int /*<<< orphan*/  isLegalFormatForPackedPixelType (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  legalFormat (scalar_t__) ; 
 int /*<<< orphan*/  legalType (scalar_t__) ; 

__attribute__((used)) static int checkMipmapArgs(GLenum internalFormat, GLenum format, GLenum type)
{
    if (!legalFormat(format) || !legalType(type)) {
	return GLU_INVALID_ENUM;
    }
    if (format == GL_STENCIL_INDEX) {
	return GLU_INVALID_ENUM;
    }

    if (!isLegalFormatForPackedPixelType(format, type)) {
	return GLU_INVALID_OPERATION;
    }

    return 0;
}