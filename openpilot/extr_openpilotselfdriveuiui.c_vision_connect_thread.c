#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  stream_bufs; } ;
struct TYPE_7__ {int /*<<< orphan*/  fds; int /*<<< orphan*/  num_fds; TYPE_1__ d; } ;
typedef  TYPE_2__ VisionPacket ;
struct TYPE_8__ {int vision_connected; int ipc_fd; int vision_connect_firstrun; int /*<<< orphan*/  lock; } ;
typedef  TYPE_3__ UIState ;

/* Variables and functions */
 int /*<<< orphan*/  VISION_STREAM_RGB_BACK ; 
 int /*<<< orphan*/  VISION_STREAM_RGB_FRONT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  do_exit ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ui_init_vision (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep (int) ; 
 int vipc_connect () ; 
 int /*<<< orphan*/  vision_subscribe (int,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void* vision_connect_thread(void *args) {
  int err;

  UIState *s = args;
  while (!do_exit) {
    usleep(100000);
    pthread_mutex_lock(&s->lock);
    bool connected = s->vision_connected;
    pthread_mutex_unlock(&s->lock);
    if (connected) continue;

    int fd = vipc_connect();
    if (fd < 0) continue;

    VisionPacket back_rp, front_rp;
    if (!vision_subscribe(fd, &back_rp, VISION_STREAM_RGB_BACK)) continue;
    if (!vision_subscribe(fd, &front_rp, VISION_STREAM_RGB_FRONT)) continue;

    pthread_mutex_lock(&s->lock);
    assert(!s->vision_connected);
    s->ipc_fd = fd;

    ui_init_vision(s,
                   back_rp.d.stream_bufs, back_rp.num_fds, back_rp.fds,
                   front_rp.d.stream_bufs, front_rp.num_fds, front_rp.fds);

    s->vision_connected = true;
    s->vision_connect_firstrun = true;
    pthread_mutex_unlock(&s->lock);
  }
  return NULL;
}