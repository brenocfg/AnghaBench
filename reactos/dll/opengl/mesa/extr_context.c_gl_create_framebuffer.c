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
struct TYPE_3__ {int /*<<< orphan*/ * Visual; } ;
typedef  int /*<<< orphan*/  GLvisual ;
typedef  TYPE_1__ GLframebuffer ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 

GLframebuffer *gl_create_framebuffer( GLvisual *visual )
{
   GLframebuffer *buffer;

   buffer = (GLframebuffer *) calloc( 1, sizeof(GLframebuffer) );
   if (!buffer) {
      return NULL;
   }

   buffer->Visual = visual;

   return buffer;
}