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
struct tun_struct {int numqueues; int /*<<< orphan*/  sndbuf; int /*<<< orphan*/ * tfiles; } ;
struct TYPE_4__ {TYPE_1__* sk; } ;
struct tun_file {TYPE_2__ socket; } ;
struct TYPE_3__ {int /*<<< orphan*/  sk_sndbuf; } ;

/* Variables and functions */
 struct tun_file* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tun_set_sndbuf(struct tun_struct *tun)
{
	struct tun_file *tfile;
	int i;

	for (i = 0; i < tun->numqueues; i++) {
		tfile = rtnl_dereference(tun->tfiles[i]);
		tfile->socket.sk->sk_sndbuf = tun->sndbuf;
	}
}