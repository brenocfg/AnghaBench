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
typedef  int uint8_t ;
struct TYPE_5__ {int ui_viz_rx; int ui_viz_rw; int uilayout_mapenabled; int /*<<< orphan*/  uilayout_sidebarcollapsed; } ;
struct TYPE_4__ {int const alert_blinking_alpha; int /*<<< orphan*/  vg; TYPE_2__ scene; } ;
typedef  TYPE_1__ UIState ;
typedef  TYPE_2__ UIScene ;
typedef  int /*<<< orphan*/  NVGpaint ;

/* Variables and functions */
 int ALERTSIZE_FULL ; 
 int ALERTSIZE_MID ; 
 int ALERTSIZE_NONE ; 
 int ALERTSIZE_SMALL ; 
 int NVG_ALIGN_BASELINE ; 
 int NVG_ALIGN_BOTTOM ; 
 int NVG_ALIGN_CENTER ; 
 int NVG_ALIGN_MIDDLE ; 
 int** alert_colors ; 
 int* alert_sizes ; 
 int bdr_s ; 
 int nav_w ; 
 int nav_ww ; 
 int /*<<< orphan*/  nvgBeginPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgFill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgFillColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgFillPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgFontFace (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nvgFontSize (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvgLinearGradient (int /*<<< orphan*/ ,int const,int const,int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgRGBA (int const,int const,int const,int const) ; 
 int /*<<< orphan*/  nvgRGBAf (double,double,double,double) ; 
 int /*<<< orphan*/  nvgRect (int /*<<< orphan*/ ,int const,int const,int const,int const) ; 
 int /*<<< orphan*/  nvgText (int /*<<< orphan*/ ,int const,int const,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvgTextAlign (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvgTextBox (int /*<<< orphan*/ ,int const,int const,int const,char const*,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 int const vwp_h ; 

__attribute__((used)) static void ui_draw_vision_alert(UIState *s, int va_size, int va_color,
                                  const char* va_text1, const char* va_text2) {
  const UIScene *scene = &s->scene;
  int ui_viz_rx = scene->ui_viz_rx;
  int ui_viz_rw = scene->ui_viz_rw;
  bool hasSidebar = !s->scene.uilayout_sidebarcollapsed;
  bool mapEnabled = s->scene.uilayout_mapenabled;
  bool longAlert1 = strlen(va_text1) > 15;

  const uint8_t *color = alert_colors[va_color];
  const int alr_s = alert_sizes[va_size];
  const int alr_x = ui_viz_rx-(mapEnabled?(hasSidebar?nav_w:(nav_ww)):0)-bdr_s;
  const int alr_w = ui_viz_rw+(mapEnabled?(hasSidebar?nav_w:(nav_ww)):0)+(bdr_s*2);
  const int alr_h = alr_s+(va_size==ALERTSIZE_NONE?0:bdr_s);
  const int alr_y = vwp_h-alr_h;

  nvgBeginPath(s->vg);
  nvgRect(s->vg, alr_x, alr_y, alr_w, alr_h);
  nvgFillColor(s->vg, nvgRGBA(color[0],color[1],color[2],(color[3]*s->alert_blinking_alpha)));
  nvgFill(s->vg);

  nvgBeginPath(s->vg);
  NVGpaint gradient = nvgLinearGradient(s->vg, alr_x, alr_y, alr_x, alr_y+alr_h,
                        nvgRGBAf(0.0,0.0,0.0,0.05), nvgRGBAf(0.0,0.0,0.0,0.35));
  nvgFillPaint(s->vg, gradient);
  nvgRect(s->vg, alr_x, alr_y, alr_w, alr_h);
  nvgFill(s->vg);

  nvgFillColor(s->vg, nvgRGBA(255, 255, 255, 255));
  nvgTextAlign(s->vg, NVG_ALIGN_CENTER | NVG_ALIGN_BASELINE);

  if (va_size == ALERTSIZE_SMALL) {
    nvgFontFace(s->vg, "sans-semibold");
    nvgFontSize(s->vg, 40*2.5);
    nvgText(s->vg, alr_x+alr_w/2, alr_y+alr_h/2+15, va_text1, NULL);
  } else if (va_size== ALERTSIZE_MID) {
    nvgFontFace(s->vg, "sans-bold");
    nvgFontSize(s->vg, 48*2.5);
    nvgText(s->vg, alr_x+alr_w/2, alr_y+alr_h/2-45, va_text1, NULL);
    nvgFontFace(s->vg, "sans-regular");
    nvgFontSize(s->vg, 36*2.5);
    nvgText(s->vg, alr_x+alr_w/2, alr_y+alr_h/2+75, va_text2, NULL);
  } else if (va_size== ALERTSIZE_FULL) {
    nvgFontSize(s->vg, (longAlert1?72:96)*2.5);
    nvgFontFace(s->vg, "sans-bold");
    nvgTextAlign(s->vg, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
    nvgTextBox(s->vg, alr_x, alr_y+(longAlert1?360:420), alr_w-60, va_text1, NULL);
    nvgFontSize(s->vg, 48*2.5);
    nvgFontFace(s->vg, "sans-regular");
    nvgTextAlign(s->vg, NVG_ALIGN_CENTER | NVG_ALIGN_BOTTOM);
    nvgTextBox(s->vg, alr_x, alr_h-(longAlert1?300:360), alr_w-60, va_text2, NULL);
  }
}