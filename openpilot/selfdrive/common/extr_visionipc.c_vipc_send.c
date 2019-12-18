#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  p ;
struct TYPE_4__ {int /*<<< orphan*/  d; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ VisionPacketWire ;
struct TYPE_5__ {int /*<<< orphan*/  num_fds; scalar_t__ fds; int /*<<< orphan*/  d; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ VisionPacket ;

/* Variables and functions */
 int /*<<< orphan*/  VIPC_MAX_FDS ; 
 int /*<<< orphan*/  assert (int) ; 
 int ipc_sendrecv_with_fds (int,int,void*,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int vipc_send(int fd, const VisionPacket *p2) {
  assert(p2->num_fds <= VIPC_MAX_FDS);

  VisionPacketWire p = {
    .type = p2->type,
    .d = p2->d,
  };
  return ipc_sendrecv_with_fds(true, fd, (void*)&p, sizeof(p), (int*)p2->fds, p2->num_fds, NULL);
}