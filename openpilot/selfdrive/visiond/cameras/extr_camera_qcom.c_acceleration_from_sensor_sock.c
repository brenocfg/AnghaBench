#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zmq_msg_t ;
struct cereal_SensorEventData_SensorVec {int /*<<< orphan*/  v; } ;
struct cereal_SensorEventData {scalar_t__ which; int /*<<< orphan*/  acceleration; } ;
struct cereal_Event {scalar_t__ which; int /*<<< orphan*/  sensorEvents; } ;
struct capn {int dummy; } ;
typedef  int /*<<< orphan*/  cereal_SensorEventData_list ;
struct TYPE_3__ {int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ cereal_Event_ptr ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  capn_free (struct capn*) ; 
 int /*<<< orphan*/  capn_get32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  capn_getp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  capn_init_mem (struct capn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int capn_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capn_root (struct capn*) ; 
 float capn_to_f32 (int /*<<< orphan*/ ) ; 
 scalar_t__ cereal_Event_sensorEvents ; 
 scalar_t__ cereal_SensorEventData_acceleration ; 
 int /*<<< orphan*/  cereal_get_SensorEventData (struct cereal_SensorEventData*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cereal_read_Event (struct cereal_Event*,TYPE_1__) ; 
 int /*<<< orphan*/  cereal_read_SensorEventData_SensorVec (struct cereal_SensorEventData_SensorVec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmq_msg_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmq_msg_data (int /*<<< orphan*/ *) ; 
 int zmq_msg_init (int /*<<< orphan*/ *) ; 
 int zmq_msg_recv (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmq_msg_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool acceleration_from_sensor_sock(void* sock, float* vs) {
  int err;

  zmq_msg_t msg;
  err = zmq_msg_init(&msg);
  assert(err == 0);

  err = zmq_msg_recv(&msg, sock, 0);
  assert(err >= 0);

  struct capn ctx;
  capn_init_mem(&ctx, zmq_msg_data(&msg), zmq_msg_size(&msg), 0);

  cereal_Event_ptr eventp;
  eventp.p = capn_getp(capn_root(&ctx), 0, 1);
  struct cereal_Event eventd;
  cereal_read_Event(&eventd, eventp);

  bool ret = false;

  if (eventd.which == cereal_Event_sensorEvents) {
    cereal_SensorEventData_list lst = eventd.sensorEvents;
    int len = capn_len(lst);
    for (int i=0; i<len; i++) {
      struct cereal_SensorEventData sensord;
      cereal_get_SensorEventData(&sensord, lst, i);

      if (sensord.which == cereal_SensorEventData_acceleration) {
        struct cereal_SensorEventData_SensorVec vecd;
        cereal_read_SensorEventData_SensorVec(&vecd, sensord.acceleration);

        int vlen = capn_len(vecd.v);
        if (vlen < 3) {
          continue; //wtf
        }
        for (int j=0; j<3; j++) {
          vs[j] = capn_to_f32(capn_get32(vecd.v, j));
        }
        ret = true;
        break;
      }
    }
  }

  capn_free(&ctx);
  zmq_msg_close(&msg);

  return ret;
}