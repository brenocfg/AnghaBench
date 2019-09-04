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
struct ra_renderpass_gl {int /*<<< orphan*/  vao; int /*<<< orphan*/  program; struct ra_renderpass_gl* priv; } ;
struct ra_renderpass {int /*<<< orphan*/  vao; int /*<<< orphan*/  program; struct ra_renderpass* priv; } ;
struct ra {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* DeleteProgram ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  gl_vao_uninit (int /*<<< orphan*/ *) ; 
 TYPE_1__* ra_gl_get (struct ra*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct ra_renderpass_gl*) ; 

__attribute__((used)) static void gl_renderpass_destroy(struct ra *ra, struct ra_renderpass *pass)
{
    GL *gl = ra_gl_get(ra);
    struct ra_renderpass_gl *pass_gl = pass->priv;
    gl->DeleteProgram(pass_gl->program);
    gl_vao_uninit(&pass_gl->vao);

    talloc_free(pass_gl);
    talloc_free(pass);
}