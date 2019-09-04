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
typedef  int /*<<< orphan*/  uint64_t ;
struct cereal_LiveLocationData {double timeOfWeek; int /*<<< orphan*/  fixMonoTime; } ;
struct cereal_Event {scalar_t__ which; int /*<<< orphan*/  liveLocationTiming; } ;
struct capn {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ cereal_Event_ptr ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  capn_free (struct capn*) ; 
 int /*<<< orphan*/  capn_getp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  capn_init_mem (struct capn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capn_root (struct capn*) ; 
 scalar_t__ cereal_Event_liveLocationTiming ; 
 int /*<<< orphan*/  cereal_read_Event (struct cereal_Event*,TYPE_1__) ; 
 int /*<<< orphan*/  cereal_read_LiveLocationData (struct cereal_LiveLocationData*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmq_msg_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmq_msg_data (int /*<<< orphan*/ *) ; 
 int zmq_msg_init (int /*<<< orphan*/ *) ; 
 int zmq_msg_recv (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmq_msg_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool gps_time_from_timing_sock(void* sock, uint64_t *mono_time, double* vs) {
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

  if (eventd.which == cereal_Event_liveLocationTiming) {
    struct cereal_LiveLocationData lld;
    cereal_read_LiveLocationData(&lld, eventd.liveLocationTiming);

    *mono_time = lld.fixMonoTime;
    *vs = lld.timeOfWeek;
    ret = true;
  }

  capn_free(&ctx);
  zmq_msg_close(&msg);

  return ret;
}