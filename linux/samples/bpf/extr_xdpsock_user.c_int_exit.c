#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xsk_umem {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  xsk; TYPE_1__* umem; } ;
struct TYPE_3__ {struct xsk_umem* umem; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  dump_stats () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_xdp_program () ; 
 int /*<<< orphan*/  xsk_socket__delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsk_umem__delete (struct xsk_umem*) ; 
 TYPE_2__** xsks ; 

__attribute__((used)) static void int_exit(int sig)
{
	struct xsk_umem *umem = xsks[0]->umem->umem;

	(void)sig;

	dump_stats();
	xsk_socket__delete(xsks[0]->xsk);
	(void)xsk_umem__delete(umem);
	remove_xdp_program();

	exit(EXIT_SUCCESS);
}