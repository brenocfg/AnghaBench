#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct yenta_socket {int /*<<< orphan*/  socket; } ;
struct resource {int end; int /*<<< orphan*/  start; } ;
struct TYPE_5__ {int map; struct resource* res; } ;
typedef  TYPE_1__ pccard_mem_map ;
struct TYPE_6__ {int member_4; int map; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ pccard_io_map ;

/* Variables and functions */
 int /*<<< orphan*/  dead_socket ; 
 int /*<<< orphan*/  yenta_set_io_map (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  yenta_set_mem_map (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  yenta_set_socket (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void yenta_clear_maps(struct yenta_socket *socket)
{
	int i;
	struct resource res = { .start = 0, .end = 0x0fff };
	pccard_io_map io = { 0, 0, 0, 0, 1 };
	pccard_mem_map mem = { .res = &res, };

	yenta_set_socket(&socket->socket, &dead_socket);
	for (i = 0; i < 2; i++) {
		io.map = i;
		yenta_set_io_map(&socket->socket, &io);
	}
	for (i = 0; i < 5; i++) {
		mem.map = i;
		yenta_set_mem_map(&socket->socket, &mem);
	}
}