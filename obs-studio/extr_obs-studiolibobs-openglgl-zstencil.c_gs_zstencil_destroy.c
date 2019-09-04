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
struct TYPE_4__ {scalar_t__ buffer; } ;
typedef  TYPE_1__ gs_zstencil_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  glDeleteRenderbuffers (int,scalar_t__*) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

void gs_zstencil_destroy(gs_zstencil_t *zs)
{
	if (zs) {
		if (zs->buffer) {
			glDeleteRenderbuffers(1, &zs->buffer);
			gl_success("glDeleteRenderbuffers");
		}

		bfree(zs);
	}
}