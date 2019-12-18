#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pfd ;
struct TYPE_4__ {int nSize; int nVersion; int cColorBits; int cDepthBits; int cStencilBits; int dwFlags; int /*<<< orphan*/  iLayerType; int /*<<< orphan*/  iPixelType; } ;
typedef  TYPE_1__ PIXELFORMATDESCRIPTOR ;

/* Variables and functions */
 int PFD_DOUBLEBUFFER ; 
 int PFD_DRAW_TO_WINDOW ; 
 int /*<<< orphan*/  PFD_MAIN_PLANE ; 
 int PFD_SUPPORT_OPENGL ; 
 int /*<<< orphan*/  PFD_TYPE_RGBA ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void init_dummy_pixel_format(PIXELFORMATDESCRIPTOR *pfd)
{
	memset(pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd->nSize = sizeof(pfd);
	pfd->nVersion = 1;
	pfd->iPixelType = PFD_TYPE_RGBA;
	pfd->cColorBits = 32;
	pfd->cDepthBits = 24;
	pfd->cStencilBits = 8;
	pfd->iLayerType = PFD_MAIN_PLANE;
	pfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
		       PFD_DOUBLEBUFFER;
}