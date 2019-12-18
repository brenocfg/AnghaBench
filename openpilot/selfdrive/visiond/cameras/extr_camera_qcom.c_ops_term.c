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
typedef  int /*<<< orphan*/  zsock_t ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_3__ {int type; } ;
typedef  TYPE_1__ CameraMsg ;

/* Variables and functions */
 int /*<<< orphan*/  ZMQ_DONTWAIT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmq_send (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zsock_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * zsock_new_push (char*) ; 
 int /*<<< orphan*/  zsock_resolve (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ops_term() {
  zsock_t *ops_sock = zsock_new_push(">inproc://cameraops");
  assert(ops_sock);

  CameraMsg msg = {.type = -1};
  zmq_send(zsock_resolve(ops_sock), &msg, sizeof(msg), ZMQ_DONTWAIT);

  zsock_destroy(&ops_sock);
}