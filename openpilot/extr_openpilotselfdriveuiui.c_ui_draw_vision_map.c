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
struct TYPE_5__ {int const ui_viz_rx; int map_valid; } ;
struct TYPE_4__ {int /*<<< orphan*/  vg; int /*<<< orphan*/  img_map; TYPE_2__ scene; } ;
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

__attribute__((used)) static void ui_draw_vision_map(UIState *s) {
  const UIScene *scene = &s->scene;
  const int map_size = 96;
  const int map_x = (scene->ui_viz_rx + (map_size * 3) + (bdr_s * 3));
  const int map_y = (footer_y + ((footer_h - map_size) / 2));
  const int map_img_size = (map_size * 1.5);
  const int map_img_x = (map_x - (map_img_size / 2));
  const int map_img_y = (map_y - (map_size / 4));

  bool map_valid = s->scene.map_valid;
  float map_img_alpha = map_valid ? 1.0f : 0.15f;
  float map_bg_alpha = map_valid ? 0.3f : 0.1f;
  NVGcolor map_bg = nvgRGBA(0, 0, 0, (255 * map_bg_alpha));
  NVGpaint map_img = nvgImagePattern(s->vg, map_img_x, map_img_y,
    map_img_size, map_img_size, 0, s->img_map, map_img_alpha);

  nvgBeginPath(s->vg);
  nvgCircle(s->vg, map_x, (map_y + (bdr_s * 1.5)), map_size);
  nvgFillColor(s->vg, map_bg);
  nvgFill(s->vg);

  nvgBeginPath(s->vg);
  nvgRect(s->vg, map_img_x, map_img_y, map_img_size, map_img_size);
  nvgFillPaint(s->vg, map_img);
  nvgFill(s->vg);
}