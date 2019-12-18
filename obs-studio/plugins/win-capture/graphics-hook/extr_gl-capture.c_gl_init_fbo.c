#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  fbo; } ;

/* Variables and functions */
 TYPE_1__ data ; 
 int /*<<< orphan*/  glGenFramebuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_error (char*,char*) ; 

__attribute__((used)) static inline bool gl_init_fbo(void)
{
	glGenFramebuffers(1, &data.fbo);
	return !gl_error("gl_init_fbo", "failed to initialize FBO");
}