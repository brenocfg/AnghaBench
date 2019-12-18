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
struct vertex_buffer {float** Win; } ;
typedef  size_t GLuint ;
typedef  size_t GLint ;
typedef  float GLfloat ;

/* Variables and functions */

__attribute__((used)) static GLfloat polygon_area( const struct vertex_buffer *vb,
                             GLuint n, const GLuint vlist[] )
{
   GLfloat area = 0.0F;
   GLint i;
   for (i=0;i<n;i++) {
      /* area = sum of trapezoids */
      GLuint j0 = vlist[i];
      GLuint j1 = vlist[(i+1)%n];
      GLfloat x0 = vb->Win[j0][0];
      GLfloat y0 = vb->Win[j0][1];
      GLfloat x1 = vb->Win[j1][0];
      GLfloat y1 = vb->Win[j1][1];
      GLfloat trapArea = (x0-x1)*(y0+y1);  /* Note: no divide by two here! */
      area += trapArea;
   }
   return area * 0.5F;     /* divide by two now! */
}