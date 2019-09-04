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
struct device {int /*<<< orphan*/  cmds; int /*<<< orphan*/  ebo; int /*<<< orphan*/  vbo; int /*<<< orphan*/  font_tex; int /*<<< orphan*/  prog; int /*<<< orphan*/  frag_shdr; int /*<<< orphan*/  vert_shdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  glDeleteBuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glDeleteProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDeleteShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDeleteTextures (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glDetachShader (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_buffer_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
device_shutdown(struct device *dev)
{
    glDetachShader(dev->prog, dev->vert_shdr);
    glDetachShader(dev->prog, dev->frag_shdr);
    glDeleteShader(dev->vert_shdr);
    glDeleteShader(dev->frag_shdr);
    glDeleteProgram(dev->prog);
    glDeleteTextures(1, &dev->font_tex);
    glDeleteBuffers(1, &dev->vbo);
    glDeleteBuffers(1, &dev->ebo);
    nk_buffer_free(&dev->cmds);
}