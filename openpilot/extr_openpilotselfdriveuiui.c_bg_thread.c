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
typedef  double uint8_t ;
struct TYPE_2__ {int status; int /*<<< orphan*/  lock; int /*<<< orphan*/  bg_cond; } ;
typedef  TYPE_1__ UIState ;
typedef  int /*<<< orphan*/  FramebufferState ;
typedef  int /*<<< orphan*/  EGLSurface ;
typedef  int /*<<< orphan*/  EGLDisplay ;

/* Variables and functions */
 int ARRAYSIZE (double**) ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 scalar_t__ GL_NO_ERROR ; 
 int /*<<< orphan*/  assert (int) ; 
 double** bg_colors ; 
 int /*<<< orphan*/  do_exit ; 
 int /*<<< orphan*/  eglSwapBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * framebuffer_init (char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (double const,double const,double const,double) ; 
 scalar_t__ glGetError () ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void* bg_thread(void* args) {
  UIState *s = args;

  EGLDisplay bg_display;
  EGLSurface bg_surface;

  FramebufferState *bg_fb = framebuffer_init("bg", 0x00001000, false,
                              &bg_display, &bg_surface, NULL, NULL);
  assert(bg_fb);

  int bg_status = -1;
  while(!do_exit) {
    pthread_mutex_lock(&s->lock);
    if (bg_status == s->status) {
      // will always be signaled if it changes?
      pthread_cond_wait(&s->bg_cond, &s->lock);
    }
    bg_status = s->status;
    pthread_mutex_unlock(&s->lock);

    assert(bg_status < ARRAYSIZE(bg_colors));
    const uint8_t *color = bg_colors[bg_status];

    glClearColor(color[0]/256.0, color[1]/256.0, color[2]/256.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    eglSwapBuffers(bg_display, bg_surface);
    assert(glGetError() == GL_NO_ERROR);
  }

  return NULL;
}