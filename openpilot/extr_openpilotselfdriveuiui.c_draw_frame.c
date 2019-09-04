#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  v; } ;
typedef  TYPE_1__ mat4 ;
struct TYPE_7__ {scalar_t__ frontview; scalar_t__ fullview; } ;
struct TYPE_6__ {size_t cur_vision_front_idx; scalar_t__ cur_vision_idx; int /*<<< orphan*/  frame_transform_loc; int /*<<< orphan*/  frame_texture_loc; int /*<<< orphan*/  frame_program; int /*<<< orphan*/ * frame_texs; int /*<<< orphan*/ * frame_front_texs; TYPE_3__ scene; TYPE_1__ rear_frame_mat; TYPE_1__ front_frame_mat; int /*<<< orphan*/ * frame_vao; } ;
typedef  TYPE_2__ UIState ;
typedef  TYPE_3__ UIScene ;

/* Variables and functions */
 scalar_t__ GL_NO_ERROR ; 
 int /*<<< orphan*/  GL_TEXTURE0 ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  glActiveTexture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindVertexArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDisableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawElements (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int /*<<< orphan*/ ) ; 
 scalar_t__ glGetError () ; 
 int /*<<< orphan*/  glUniform1i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUniformMatrix4fv (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void draw_frame(UIState *s) {
  const UIScene *scene = &s->scene;

  float x1, x2, y1, y2;
  if (s->scene.frontview) {
    glBindVertexArray(s->frame_vao[1]);
  } else {
    glBindVertexArray(s->frame_vao[0]);
  }

  mat4 *out_mat;
  if (s->scene.frontview || s->scene.fullview) {
    out_mat = &s->front_frame_mat;
  } else {
    out_mat = &s->rear_frame_mat;
  }
  glActiveTexture(GL_TEXTURE0);
  if (s->scene.frontview && s->cur_vision_front_idx >= 0) {
    glBindTexture(GL_TEXTURE_2D, s->frame_front_texs[s->cur_vision_front_idx]);
  } else if (!scene->frontview && s->cur_vision_idx >= 0) {
    glBindTexture(GL_TEXTURE_2D, s->frame_texs[s->cur_vision_idx]);
  }

  glUseProgram(s->frame_program);
  glUniform1i(s->frame_texture_loc, 0);
  glUniformMatrix4fv(s->frame_transform_loc, 1, GL_TRUE, out_mat->v);

  assert(glGetError() == GL_NO_ERROR);
  glEnableVertexAttribArray(0);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (const void*)0);
  glDisableVertexAttribArray(0);
  glBindVertexArray(0);
}