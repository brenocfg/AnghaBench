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
struct TYPE_4__ {struct TYPE_4__* BackAlpha; struct TYPE_4__* FrontAlpha; struct TYPE_4__* Stencil; struct TYPE_4__* Accum; struct TYPE_4__* Depth; } ;
typedef  TYPE_1__ GLframebuffer ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void gl_destroy_framebuffer( GLframebuffer *buffer )
{
   if (buffer) {
      if (buffer->Depth) {
         free( buffer->Depth );
      }
      if (buffer->Accum) {
         free( buffer->Accum );
      }
      if (buffer->Stencil) {
         free( buffer->Stencil );
      }
      if (buffer->FrontAlpha) {
         free( buffer->FrontAlpha );
      }
      if (buffer->BackAlpha) {
         free( buffer->BackAlpha );
      }
      free(buffer);
   }
}