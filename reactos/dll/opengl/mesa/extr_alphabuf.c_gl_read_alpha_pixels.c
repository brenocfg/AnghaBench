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
typedef  size_t GLuint ;
typedef  scalar_t__ GLubyte ;
typedef  int /*<<< orphan*/  GLint ;
typedef  int /*<<< orphan*/  GLcontext ;

/* Variables and functions */
 scalar_t__* ALPHA_ADDR (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

void gl_read_alpha_pixels( GLcontext* ctx,
                           GLuint n, const GLint x[], const GLint y[],
                           GLubyte alpha[], const GLubyte mask[] )
{
   GLuint i;
   for (i=0;i<n;i++) {
      if (mask[i]) {
         GLubyte *aptr = ALPHA_ADDR( x[i], y[i] );
         alpha[i] = *aptr;
      }
   }
}