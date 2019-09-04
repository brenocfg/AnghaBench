#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tun_struct {int filter_attached; int /*<<< orphan*/ * tfiles; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;
struct tun_file {TYPE_1__ socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_sock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (int /*<<< orphan*/ ) ; 
 struct tun_file* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_detach_filter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tun_detach_filter(struct tun_struct *tun, int n)
{
	int i;
	struct tun_file *tfile;

	for (i = 0; i < n; i++) {
		tfile = rtnl_dereference(tun->tfiles[i]);
		lock_sock(tfile->socket.sk);
		sk_detach_filter(tfile->socket.sk);
		release_sock(tfile->socket.sk);
	}

	tun->filter_attached = false;
}