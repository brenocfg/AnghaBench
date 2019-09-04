#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zsock_t ;
typedef  int /*<<< orphan*/  zpoller_t ;
typedef  int /*<<< orphan*/  zmq_msg_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  cmsg ;
struct TYPE_8__ {int last_sag_ts; float last_sag_acc_z; int global_time_offset; int phase_request; int using_pll; } ;
struct TYPE_7__ {int type; scalar_t__ camera_num; int /*<<< orphan*/  grey_frac; } ;
struct TYPE_6__ {TYPE_4__ rear; TYPE_4__ front; } ;
typedef  TYPE_1__ DualCameraState ;
typedef  TYPE_2__ CameraMsg ;

/* Variables and functions */
 int CAMERA_MSG_AUTOEXPOSE ; 
 int /*<<< orphan*/  LOGD (char*,int) ; 
 int acceleration_from_sensor_sock (void*,float*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  do_autoexposure (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_autofocus (TYPE_4__*) ; 
 int /*<<< orphan*/  do_exit ; 
 scalar_t__ gps_time_from_timing_sock (void*,int*,double*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int nanos_since_boot () ; 
 int /*<<< orphan*/  set_thread_name (char*) ; 
 int /*<<< orphan*/  zmq_msg_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmq_msg_data (int /*<<< orphan*/ *) ; 
 int zmq_msg_init (int /*<<< orphan*/ *) ; 
 int zmq_msg_recv (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int zmq_msg_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpoller_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * zpoller_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ zpoller_wait (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zsock_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * zsock_new_pull (char*) ; 
 int /*<<< orphan*/ * zsock_new_sub (char*,char*) ; 
 void* zsock_resolve (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void* ops_thread(void* arg) {
  int err;
  DualCameraState *s = (DualCameraState*)arg;

  set_thread_name("camera_settings");

  zsock_t *cameraops = zsock_new_pull("@inproc://cameraops");
  assert(cameraops);

  zsock_t *sensor_sock = zsock_new_sub(">tcp://127.0.0.1:8003", "");
  assert(sensor_sock);

  zsock_t *livelocationtiming_sock = zsock_new_sub(">tcp://127.0.0.1:8049", "");
  assert(livelocationtiming_sock);

  zsock_t *terminate = zsock_new_sub(">inproc://terminate", "");
  assert(terminate);

  zpoller_t *poller = zpoller_new(cameraops, sensor_sock, livelocationtiming_sock, terminate, NULL);
  assert(poller);

  while (!do_exit) {

    zsock_t *which = (zsock_t*)zpoller_wait(poller, -1);
    if (which == terminate || which == NULL) {
      break;
    }
    void* sockraw = zsock_resolve(which);

    if (which == cameraops) {
      zmq_msg_t msg;
      err = zmq_msg_init(&msg);
      assert(err == 0);

      err = zmq_msg_recv(&msg, sockraw, 0);
      assert(err >= 0);

      CameraMsg cmsg;
      if (zmq_msg_size(&msg) == sizeof(cmsg)) {
        memcpy(&cmsg, zmq_msg_data(&msg), zmq_msg_size(&msg));

        LOGD("cameraops %d", cmsg.type);

        if (cmsg.type == CAMERA_MSG_AUTOEXPOSE) {
          if (cmsg.camera_num == 0) {
            do_autoexposure(&s->rear, cmsg.grey_frac);
            do_autofocus(&s->rear);
          } else {
            do_autoexposure(&s->front, cmsg.grey_frac);
          }
        } else if (cmsg.type == -1) {
          break;
        }
      }

      zmq_msg_close(&msg);

    } else if (which == sensor_sock) {
      float vs[3] = {0.0};
      bool got_accel = acceleration_from_sensor_sock(sockraw, vs);

      uint64_t ts = nanos_since_boot();
      if (got_accel && ts - s->rear.last_sag_ts > 10000000) { // 10 ms
        s->rear.last_sag_ts = ts;
        s->rear.last_sag_acc_z = -vs[2];
      }
    } else if (which == livelocationtiming_sock) {
      uint64_t mono_time;
      double gps_time;
      if (gps_time_from_timing_sock(sockraw, &mono_time, &gps_time)) {
        s->rear.global_time_offset = (uint64_t)(gps_time*1e9) - mono_time;
        //LOGW("%f %lld  = %lld", gps_time, mono_time, s->rear.global_time_offset);
        s->rear.phase_request = 10000000;
        s->rear.using_pll = true;
      }
    }
  }

  zpoller_destroy(&poller);
  zsock_destroy(&cameraops);
  zsock_destroy(&sensor_sock);
  zsock_destroy(&terminate);

  return NULL;
}