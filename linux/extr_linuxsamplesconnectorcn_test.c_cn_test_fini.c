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
struct TYPE_5__ {int /*<<< orphan*/  val; } ;
struct TYPE_4__ {scalar_t__ sk_socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  cn_del_callback (TYPE_2__*) ; 
 TYPE_2__ cn_test_id ; 
 int /*<<< orphan*/  cn_test_timer ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 TYPE_1__* nls ; 
 int /*<<< orphan*/  sock_release (scalar_t__) ; 

__attribute__((used)) static void cn_test_fini(void)
{
	del_timer_sync(&cn_test_timer);
	cn_del_callback(&cn_test_id);
	cn_test_id.val--;
	cn_del_callback(&cn_test_id);
	if (nls && nls->sk_socket)
		sock_release(nls->sk_socket);
}