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
typedef  int /*<<< orphan*/  NVGpaint ;
typedef  int /*<<< orphan*/  NVGcontext ;
typedef  int /*<<< orphan*/  FramebufferState ;
typedef  int /*<<< orphan*/  EGLSurface ;
typedef  int /*<<< orphan*/  EGLDisplay ;

/* Variables and functions */
 int /*<<< orphan*/  GL_BLEND ; 
 int GL_COLOR_BUFFER_BIT ; 
 scalar_t__ GL_NO_ERROR ; 
 int /*<<< orphan*/  GL_ONE_MINUS_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_SRC_ALPHA ; 
 int GL_STENCIL_BUFFER_BIT ; 
 double M_PI ; 
 int NVG_ALIGN_CENTER ; 
 int NVG_ALIGN_TOP ; 
 int NVG_ANTIALIAS ; 
 int NVG_STENCIL_STROKES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  eglSwapBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * framebuffer_init (char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  glBlendFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int) ; 
 int /*<<< orphan*/  glClearColor (double,double,double,double) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 scalar_t__ glGetError () ; 
 int /*<<< orphan*/  nvgBeginFrame (int /*<<< orphan*/ *,int,int,float) ; 
 int /*<<< orphan*/  nvgBeginPath (int /*<<< orphan*/ *) ; 
 int nvgCreateFont (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * nvgCreateGLES3 (int) ; 
 int nvgCreateImage (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgEndFrame (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvgFill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvgFillPaint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgFontSize (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  nvgImagePattern (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int,float) ; 
 int /*<<< orphan*/  nvgLinearGradient (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgRGBA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvgRect (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  nvgRestore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvgRotate (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  nvgSave (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvgText (int /*<<< orphan*/ *,int,int,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvgTextAlign (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nvgTranslate (int /*<<< orphan*/ *,int,int) ; 

int main(int argc, char** argv) {
  int err;

  const char* spintext = NULL;
  if (argc >= 2) {
    spintext = argv[1];
  }

  // spinner
  int fb_w, fb_h;
  EGLDisplay display;
  EGLSurface surface;
  FramebufferState *fb = framebuffer_init("spinner", 0x00001000, false,
                     &display, &surface, &fb_w, &fb_h);
  assert(fb);

  NVGcontext *vg = nvgCreateGLES3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
  assert(vg);

  int font = nvgCreateFont(vg, "Bold", "../../assets/OpenSans-SemiBold.ttf");
  assert(font >= 0);

  int spinner_img = nvgCreateImage(vg, "../../assets/img_spinner_track.png", 0);
  assert(spinner_img >= 0);
  int spinner_img_s = 360;
  int spinner_img_x = ((fb_w/2)-(spinner_img_s/2));
  int spinner_img_y = 260;
  int spinner_img_xc = (fb_w/2);
  int spinner_img_yc = (fb_h/2)-100;
  int spinner_comma_img = nvgCreateImage(vg, "../../assets/img_spinner_comma.png", 0);
  assert(spinner_comma_img >= 0);

  for (int cnt = 0; ; cnt++) {
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    nvgBeginFrame(vg, fb_w, fb_h, 1.0f);

    // background
    nvgBeginPath(vg);
    NVGpaint bg = nvgLinearGradient(vg, fb_w, 0, fb_w, fb_h,
    nvgRGBA(0, 0, 0, 175), nvgRGBA(0, 0, 0, 255));
    nvgFillPaint(vg, bg);
    nvgRect(vg, 0, 0, fb_w, fb_h);
    nvgFill(vg);

    // spin track
    nvgSave(vg);
    nvgTranslate(vg, spinner_img_xc, spinner_img_yc);
    nvgRotate(vg, (3.75*M_PI * cnt/120.0));
    nvgTranslate(vg, -spinner_img_xc, -spinner_img_yc);
    NVGpaint spinner_imgPaint = nvgImagePattern(vg, spinner_img_x, spinner_img_y,
      spinner_img_s, spinner_img_s, 0, spinner_img, 0.6f);
    nvgBeginPath(vg);
    nvgFillPaint(vg, spinner_imgPaint);
    nvgRect(vg, spinner_img_x, spinner_img_y, spinner_img_s, spinner_img_s);
    nvgFill(vg);
    nvgRestore(vg);

    // comma
    NVGpaint comma_imgPaint = nvgImagePattern(vg, spinner_img_x, spinner_img_y,
      spinner_img_s, spinner_img_s, 0, spinner_comma_img, 1.0f);
    nvgBeginPath(vg);
    nvgFillPaint(vg, comma_imgPaint);
    nvgRect(vg, spinner_img_x, spinner_img_y, spinner_img_s, spinner_img_s);
    nvgFill(vg);

    // message
    if (spintext) {
      nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_TOP);
      nvgFontSize(vg, 96.0f);
      nvgText(vg, fb_w/2, (fb_h*2/3)+24, spintext, NULL);
    }

    nvgEndFrame(vg);
    eglSwapBuffers(display, surface);
    assert(glGetError() == GL_NO_ERROR);
  }

  return 0;
}