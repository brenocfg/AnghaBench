#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  events; int /*<<< orphan*/  fd; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ zmq_pollitem_t ;
typedef  int /*<<< orphan*/  sighandler_t ;
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_18__ {int v_ego; } ;
struct TYPE_20__ {float const light_sensor; scalar_t__ awake_timeout; scalar_t__ volume_timeout; scalar_t__ speed_lim_off_timeout; scalar_t__ is_metric_timeout; scalar_t__ limit_set_speed_timeout; int /*<<< orphan*/  lock; int /*<<< orphan*/  bg_cond; int /*<<< orphan*/  surface; int /*<<< orphan*/  display; TYPE_1__ scene; scalar_t__ vision_connected; scalar_t__ awake; int /*<<< orphan*/  touch_fd; } ;
typedef  TYPE_3__ UIState ;
struct TYPE_21__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ TouchState ;

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  LOGW (char*,...) ; 
 int /*<<< orphan*/  PRIO_PROCESS ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  ZMQ_POLLIN ; 
 int access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bg_thread ; 
 int /*<<< orphan*/  do_exit ; 
 int /*<<< orphan*/  eglSwapBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  glFinish () ; 
 int is_leon () ; 
 int /*<<< orphan*/  light_sensor_thread ; 
 int min (int,int) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_is_metric (TYPE_3__*) ; 
 int /*<<< orphan*/  read_limit_set_speed (TYPE_3__*) ; 
 int /*<<< orphan*/  read_speed_lim_off (TYPE_3__*) ; 
 int /*<<< orphan*/  set_awake (TYPE_3__*,int) ; 
 int /*<<< orphan*/  set_brightness (TYPE_3__*,int) ; 
 scalar_t__ set_do_exit ; 
 int /*<<< orphan*/  set_volume (TYPE_3__*,int) ; 
 int /*<<< orphan*/  setpriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slplay_destroy () ; 
 int /*<<< orphan*/  touch_init (TYPE_4__*) ; 
 int touch_read (TYPE_4__*,int*,int*) ; 
 int /*<<< orphan*/  ui_draw (TYPE_3__*) ; 
 int /*<<< orphan*/  ui_init (TYPE_3__*) ; 
 int /*<<< orphan*/  ui_sound_init (char**) ; 
 int /*<<< orphan*/  ui_update (TYPE_3__*) ; 
 int /*<<< orphan*/  usleep (int) ; 
 int /*<<< orphan*/  vision_connect_thread ; 
 int zmq_poll (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zsys_handler_set (int /*<<< orphan*/ *) ; 

int main() {
  int err;
  setpriority(PRIO_PROCESS, 0, -14);

  zsys_handler_set(NULL);
  signal(SIGINT, (sighandler_t)set_do_exit);

  UIState uistate;
  UIState *s = &uistate;
  ui_init(s);

  pthread_t connect_thread_handle;
  err = pthread_create(&connect_thread_handle, NULL,
                       vision_connect_thread, s);
  assert(err == 0);

  pthread_t light_sensor_thread_handle;
  err = pthread_create(&light_sensor_thread_handle, NULL,
                       light_sensor_thread, s);
  assert(err == 0);

  pthread_t bg_thread_handle;
  err = pthread_create(&bg_thread_handle, NULL,
                       bg_thread, s);
  assert(err == 0);

  TouchState touch = {0};
  touch_init(&touch);
  s->touch_fd = touch.fd;

  char* error = NULL;
  ui_sound_init(&error);
  if (error) {
    LOGW(error);
    exit(1);
  }

  // light sensor scaling params
  const int EON = (access("/EON", F_OK) != -1);
  const int LEON = is_leon();

  const float BRIGHTNESS_B = LEON? 10.0 : 5.0;
  const float BRIGHTNESS_M = LEON? 2.6 : 1.3;
  #define NEO_BRIGHTNESS 100

  float smooth_brightness = BRIGHTNESS_B;

  set_volume(s, 0);
#ifdef DEBUG_FPS
  vipc_t1 = millis_since_boot();
  double t1 = millis_since_boot();
  int draws = 0, old_draws = 0;
#endif //DEBUG_FPS
  while (!do_exit) {
    bool should_swap = false;
    if (!s->vision_connected) {
      // Delay a while to avoid 9% cpu usage while car is not started and user is keeping touching on the screen.
      // Don't hold the lock while sleeping, so that vision_connect_thread have chances to get the lock.
      usleep(30 * 1000);
    }
    pthread_mutex_lock(&s->lock);

    if (EON) {
      // light sensor is only exposed on EONs

      float clipped_brightness = (s->light_sensor*BRIGHTNESS_M) + BRIGHTNESS_B;
      if (clipped_brightness > 255) clipped_brightness = 255;
      smooth_brightness = clipped_brightness * 0.01 + smooth_brightness * 0.99;
      set_brightness(s, (int)smooth_brightness);
    } else {
      // compromise for bright and dark envs
      set_brightness(s, NEO_BRIGHTNESS);
    }

    if (!s->vision_connected) {
      // Car is not started, keep in idle state and awake on touch events
      zmq_pollitem_t polls[1] = {{0}};
      polls[0].fd = s->touch_fd;
      polls[0].events = ZMQ_POLLIN;
      int ret = zmq_poll(polls, 1, 0);
      if (ret < 0)
        LOGW("poll failed (%d)", ret);
      else if (ret > 0) {
        // awake on any touch
        int touch_x = -1, touch_y = -1;
        int touched = touch_read(&touch, &touch_x, &touch_y);
        if (touched == 1) {
          set_awake(s, true);
        }
      }
    } else {
      // Car started, fetch a new rgb image from ipc and peek for zmq events.
      ui_update(s);
      if(!s->vision_connected) {
        // Visiond process is just stopped, force a redraw to make screen blank again.
        ui_draw(s);
        glFinish();
        should_swap = true;
      }
    }
    // manage wakefulness
    if (s->awake_timeout > 0) {
      s->awake_timeout--;
    } else {
      set_awake(s, false);
    }
    // Don't waste resources on drawing in case screen is off or car is not started.
    if (s->awake && s->vision_connected) {
      ui_draw(s);
      glFinish();
      should_swap = true;
#ifdef DEBUG_FPS
      draws++;
      double t2 = millis_since_boot();
      const double interval = 30.;
      if(t2 - t1 >= interval * 1000.) {
        printf("ui draw fps: %.2f\n",((double)(draws - old_draws)) / interval) ;
        t1 = t2;
        old_draws = draws;
      }
#endif
    }

    if (s->volume_timeout > 0) {
      s->volume_timeout--;
    } else {
      int volume = min(13, 11 + s->scene.v_ego / 15);  // up one notch every 15 m/s, starting at 11
      set_volume(s, volume);
    }

    if (s->speed_lim_off_timeout > 0) {
      s->speed_lim_off_timeout--;
    } else {
      read_speed_lim_off(s);
    }

    if (s->is_metric_timeout > 0) {
      s->is_metric_timeout--;
    } else {
      read_is_metric(s);
    }

    if (s->limit_set_speed_timeout > 0) {
      s->limit_set_speed_timeout--;
    } else {
      read_limit_set_speed(s);
    }

    pthread_mutex_unlock(&s->lock);

    // the bg thread needs to be scheduled, so the main thread needs time without the lock
    // safe to do this outside the lock?
    if (should_swap) {
      eglSwapBuffers(s->display, s->surface);
    }
  }

  set_awake(s, true);

  slplay_destroy();

  // wake up bg thread to exit
  pthread_mutex_lock(&s->lock);
  pthread_cond_signal(&s->bg_cond);
  pthread_mutex_unlock(&s->lock);
  err = pthread_join(bg_thread_handle, NULL);
  assert(err == 0);

  err = pthread_join(connect_thread_handle, NULL);
  assert(err == 0);

  return 0;
}