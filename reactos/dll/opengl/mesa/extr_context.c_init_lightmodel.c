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
struct gl_lightmodel {void* TwoSide; void* LocalViewer; int /*<<< orphan*/  Ambient; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSIGN_4V (int /*<<< orphan*/ ,float,float,float,float) ; 
 void* GL_FALSE ; 

__attribute__((used)) static void init_lightmodel( struct gl_lightmodel *lm )
{
   ASSIGN_4V( lm->Ambient, 0.2f, 0.2f, 0.2f, 1.0f );
   lm->LocalViewer = GL_FALSE;
   lm->TwoSide = GL_FALSE;
}