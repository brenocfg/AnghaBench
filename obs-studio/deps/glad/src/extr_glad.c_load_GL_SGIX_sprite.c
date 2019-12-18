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
typedef  scalar_t__ PFNGLSPRITEPARAMETERIVSGIXPROC ;
typedef  scalar_t__ PFNGLSPRITEPARAMETERISGIXPROC ;
typedef  scalar_t__ PFNGLSPRITEPARAMETERFVSGIXPROC ;
typedef  scalar_t__ PFNGLSPRITEPARAMETERFSGIXPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_SGIX_sprite ; 
 scalar_t__ glad_glSpriteParameterfSGIX ; 
 scalar_t__ glad_glSpriteParameterfvSGIX ; 
 scalar_t__ glad_glSpriteParameteriSGIX ; 
 scalar_t__ glad_glSpriteParameterivSGIX ; 

__attribute__((used)) static void load_GL_SGIX_sprite(GLADloadproc load) {
	if(!GLAD_GL_SGIX_sprite) return;
	glad_glSpriteParameterfSGIX = (PFNGLSPRITEPARAMETERFSGIXPROC)load("glSpriteParameterfSGIX");
	glad_glSpriteParameterfvSGIX = (PFNGLSPRITEPARAMETERFVSGIXPROC)load("glSpriteParameterfvSGIX");
	glad_glSpriteParameteriSGIX = (PFNGLSPRITEPARAMETERISGIXPROC)load("glSpriteParameteriSGIX");
	glad_glSpriteParameterivSGIX = (PFNGLSPRITEPARAMETERIVSGIXPROC)load("glSpriteParameterivSGIX");
}