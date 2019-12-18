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
struct TYPE_5__ {TYPE_1__* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  client; } ;
typedef  TYPE_1__ RIORap ;
typedef  TYPE_2__ RIODesc ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 int /*<<< orphan*/  r_socket_new_from_fd (int) ; 

__attribute__((used)) static bool __rap_accept(RIO *io, RIODesc *desc, int fd) {
	RIORap *rap = desc? desc->data: NULL;
	if (rap && fd != -1) {
		rap->client = r_socket_new_from_fd (fd);
		return true;
	}
	return false;
}