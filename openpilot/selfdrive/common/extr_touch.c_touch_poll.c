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
struct pollfd {int events; int revents; int /*<<< orphan*/  fd; } ;
struct input_event {int type; int value; int /*<<< orphan*/  code; } ;
typedef  int /*<<< orphan*/  event ;
struct TYPE_3__ {int last_x; int last_y; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ TouchState ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_TRACKING_ID ; 
#define  EV_ABS 128 
 int POLLIN ; 
 int /*<<< orphan*/  assert (int) ; 
 int poll (struct pollfd*,int,int) ; 
 int read (int /*<<< orphan*/ ,struct input_event*,int) ; 

int touch_poll(TouchState *s, int* out_x, int* out_y, int timeout) {
  assert(out_x && out_y);
  bool up = false;
  while (true) {
    struct pollfd polls[] = {{
      .fd = s->fd,
      .events = POLLIN,
    }};
    int err = poll(polls, 1, timeout);
    if (err < 0) {
      return -1;
    }
    if (!(polls[0].revents & POLLIN)) {
      break;
    }

    struct input_event event;
    err = read(polls[0].fd, &event, sizeof(event));
    if (err < sizeof(event)) {
      return -1;
    }

    switch (event.type) {
    case EV_ABS:
      if (event.code == ABS_MT_POSITION_X) {
        s->last_x = event.value;
      } else if (event.code == ABS_MT_POSITION_Y) {
        s->last_y = event.value;
      } else if (event.code == ABS_MT_TRACKING_ID && event.value != -1) {
        up = true;
      }
      break;
    default:
      break;
    }
  }
  if (up) {
    // adjust for flippening
    *out_x = s->last_y;
    *out_y = 1080 - s->last_x;
  }
  return up;
}