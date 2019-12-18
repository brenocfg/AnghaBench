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
 int SPINTEXT_LENGTH ; 
 scalar_t__ _binary_img_spinner_comma_png_end ; 
 scalar_t__ _binary_img_spinner_comma_png_start ; 
 scalar_t__ _binary_img_spinner_track_png_end ; 
 scalar_t__ _binary_img_spinner_track_png_start ; 
 scalar_t__ _binary_opensans_semibold_ttf_end ; 
 scalar_t__ _binary_opensans_semibold_ttf_start ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  eglSwapBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ ) ; 
 float fmax (double,float) ; 
 float fmin (double,float) ; 
 int /*<<< orphan*/ * framebuffer_init (char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  glBlendFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int) ; 
 int /*<<< orphan*/  glClearColor (double,double,double,double) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 scalar_t__ glGetError () ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int /*<<< orphan*/  nvgBeginFrame (int /*<<< orphan*/ *,int,int,float) ; 
 int /*<<< orphan*/  nvgBeginPath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvgBoxGradient (int /*<<< orphan*/ *,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvgCreateFontMem (int /*<<< orphan*/ *,char*,unsigned char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nvgCreateGLES3 (int) ; 
 int nvgCreateImageMem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  nvgEndFrame (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvgFill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvgFillPaint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgFontSize (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  nvgImagePattern (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int,float) ; 
 int /*<<< orphan*/  nvgLinearGradient (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvgRGB (int,int,int) ; 
 int /*<<< orphan*/  nvgRGBA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvgRect (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  nvgRestore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvgRotate (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  nvgRoundedRect (int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  nvgSave (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvgText (int /*<<< orphan*/ *,int,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvgTextAlign (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nvgTranslate (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ stdin_input_available () ; 
 size_t strcspn (char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

int spin(int argc, char** argv) {
  int err;

  bool draw_progress = false;
  float progress_val = 0.0;

  char spintext[SPINTEXT_LENGTH];
  spintext[0] = 0;

  const char* spintext_arg = NULL;
  if (argc >= 2) {
    strncpy(spintext, argv[1], SPINTEXT_LENGTH);
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

  int font = nvgCreateFontMem(vg, "Bold", (unsigned char*)_binary_opensans_semibold_ttf_start, _binary_opensans_semibold_ttf_end-_binary_opensans_semibold_ttf_start, 0);
  assert(font >= 0);

  int spinner_img = nvgCreateImageMem(vg, 0, (unsigned char*)_binary_img_spinner_track_png_start, _binary_img_spinner_track_png_end - _binary_img_spinner_track_png_start);
  assert(spinner_img >= 0);
  int spinner_img_s = 360;
  int spinner_img_x = ((fb_w/2)-(spinner_img_s/2));
  int spinner_img_y = 260;
  int spinner_img_xc = (fb_w/2);
  int spinner_img_yc = (fb_h/2)-100;
  int spinner_comma_img = nvgCreateImageMem(vg, 0, (unsigned char*)_binary_img_spinner_comma_png_start, _binary_img_spinner_comma_png_end - _binary_img_spinner_comma_png_start);
  assert(spinner_comma_img >= 0);

  for (int cnt = 0; ; cnt++) {
    // Check stdin for new text
    if (stdin_input_available()){
      fgets(spintext, SPINTEXT_LENGTH, stdin);
      spintext[strcspn(spintext, "\n")] = 0;

      // Check if number (update progress bar)
      size_t len = strlen(spintext);
      bool is_number = len > 0;
      for (int i = 0; i < len; i++){
        if (!isdigit(spintext[i])){
          is_number = false;
          break;
        }
      }

      if (is_number) {
        progress_val = (float)(atoi(spintext)) / 100.0;
        progress_val = fmin(1.0, progress_val);
        progress_val = fmax(0.0, progress_val);
      }

      draw_progress = is_number;
    }

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

    if (draw_progress){
      // draw progress bar
      int progress_width = 1000;
      int progress_x = fb_w/2-progress_width/2;
      int progress_y = 775;
      int progress_height = 25;

      NVGpaint paint = nvgBoxGradient(
          vg, progress_x + 1, progress_y + 1,
          progress_width - 2, progress_height, 3, 4, nvgRGB(27, 27, 27), nvgRGB(27, 27, 27));
      nvgBeginPath(vg);
      nvgRoundedRect(vg, progress_x, progress_y, progress_width, progress_height, 12);
      nvgFillPaint(vg, paint);
      nvgFill(vg);

      int bar_pos = ((progress_width - 2) * progress_val);

      paint = nvgBoxGradient(
          vg, progress_x, progress_y,
          bar_pos+1.5f, progress_height-1, 3, 4,
          nvgRGB(245, 245, 245), nvgRGB(105, 105, 105));

      nvgBeginPath(vg);
      nvgRoundedRect(
          vg, progress_x+1, progress_y+1,
          bar_pos, progress_height-2, 12);
      nvgFillPaint(vg, paint);
      nvgFill(vg);
    } else {
      // message
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