#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int w; int h; } ;
typedef  TYPE_1__ stbi__gif ;
typedef  int /*<<< orphan*/  stbi__context ;

/* Variables and functions */
 int /*<<< orphan*/  stbi__gif_header (int /*<<< orphan*/ *,TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  stbi__rewind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stbi__gif_info_raw(stbi__context *s, int *x, int *y, int *comp)
{
   stbi__gif g;
   if (!stbi__gif_header(s, &g, comp, 1)) {
      stbi__rewind( s );
      return 0;
   }
   if (x) *x = g.w;
   if (y) *y = g.h;
   return 1;
}