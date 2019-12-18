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
typedef  enum shape { ____Placeholder_shape } shape ;
typedef  enum rotation { ____Placeholder_rotation } rotation ;

/* Variables and functions */
 int /*<<< orphan*/ * colors ; 
 int /*<<< orphan*/  draw_shape_full (int,int /*<<< orphan*/ ,int,int,int,int,int,unsigned char*) ; 

__attribute__((used)) static void draw_shape(enum shape shape,
                       int x,
                       int y,
                       int w,
                       int h,
                       enum rotation rot,
                       unsigned char *buffer)
{
    draw_shape_full(shape, colors[shape], x, y, w, h, rot, buffer);
}