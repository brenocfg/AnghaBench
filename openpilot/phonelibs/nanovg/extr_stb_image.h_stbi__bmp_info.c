#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int img_x; int img_y; } ;
typedef  TYPE_1__ stbi__context ;
struct TYPE_8__ {int all_a; scalar_t__ ma; } ;
typedef  TYPE_2__ stbi__bmp_data ;

/* Variables and functions */
 void* stbi__bmp_parse_header (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stbi__rewind (TYPE_1__*) ; 

__attribute__((used)) static int stbi__bmp_info(stbi__context *s, int *x, int *y, int *comp)
{
   void *p;
   stbi__bmp_data info;

   info.all_a = 255;   
   p = stbi__bmp_parse_header(s, &info);
   stbi__rewind( s );
   if (p == NULL)
      return 0;
   *x = s->img_x;
   *y = s->img_y;
   *comp = info.ma ? 4 : 3;
   return 1;
}