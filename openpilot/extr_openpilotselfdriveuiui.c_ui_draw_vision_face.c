#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int const ui_viz_rx; scalar_t__ monitoring_active; } ;
struct TYPE_4__ {int /*<<< orphan*/  vg; int /*<<< orphan*/  img_face; TYPE_2__ scene; } ;
typedef  TYPE_1__ UIState ;
typedef  TYPE_2__ UIScene ;
typedef  int /*<<< orphan*/  NVGpaint ;
typedef  int /*<<< orphan*/  NVGcolor ;

/* Variables and functions */
 int bdr_s ; 
 int const footer_h ; 
 int const footer_y ; 
 int /*<<< orphan*/  nvgBeginPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgCircle (int /*<<< orphan*/ ,int const,int const,int const) ; 
 int /*<<< orphan*/  nvgFill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgFillColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgFillPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgImagePattern (int /*<<< orphan*/ ,int const,int const,int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  nvgRGBA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvgRect (int /*<<< orphan*/ ,int const,int const,int const,int const) ; 

__attribute__((used)) static void ui_draw_vision_face(UIState *s) {
  const UIScene *scene = &s->scene;
  const int face_size = 96;
  const int face_x = (scene->ui_viz_rx + face_size + (bdr_s * 2));
  const int face_y = (footer_y + ((footer_h - face_size) / 2));
  const int face_img_size = (face_size * 1.5);
  const int face_img_x = (face_x - (face_img_size / 2));
  const int face_img_y = (face_y - (face_size / 4));
  float face_img_alpha = scene->monitoring_active ? 1.0f : 0.15f;
  float face_bg_alpha = scene->monitoring_active ? 0.3f : 0.1f;
  NVGcolor face_bg = nvgRGBA(0, 0, 0, (255 * face_bg_alpha));
  NVGpaint face_img = nvgImagePattern(s->vg, face_img_x, face_img_y,
    face_img_size, face_img_size, 0, s->img_face, face_img_alpha);

  nvgBeginPath(s->vg);
  nvgCircle(s->vg, face_x, (face_y + (bdr_s * 1.5)), face_size);
  nvgFillColor(s->vg, face_bg);
  nvgFill(s->vg);

  nvgBeginPath(s->vg);
  nvgRect(s->vg, face_img_x, face_img_y, face_img_size, face_img_size);
  nvgFillPaint(s->vg, face_img);
  nvgFill(s->vg);
}