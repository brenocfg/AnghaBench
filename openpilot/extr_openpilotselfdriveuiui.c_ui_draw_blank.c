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
typedef  int /*<<< orphan*/  UIState ;

/* Variables and functions */
 int GL_COLOR_BUFFER_BIT ; 
 int GL_STENCIL_BUFFER_BIT ; 
 int /*<<< orphan*/  glClear (int) ; 
 int /*<<< orphan*/  glClearColor (double,double,double,double) ; 

__attribute__((used)) static void ui_draw_blank(UIState *s) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}