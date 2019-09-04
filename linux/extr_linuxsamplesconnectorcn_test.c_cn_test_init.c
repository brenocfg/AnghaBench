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
struct TYPE_6__ {int /*<<< orphan*/  val; int /*<<< orphan*/  idx; } ;
struct TYPE_5__ {scalar_t__ sk_socket; } ;

/* Variables and functions */
 int cn_add_callback (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cn_del_callback (TYPE_2__*) ; 
 int /*<<< orphan*/  cn_test_callback ; 
 TYPE_2__ cn_test_id ; 
 int /*<<< orphan*/  cn_test_name ; 
 int /*<<< orphan*/  cn_test_timer ; 
 int /*<<< orphan*/  cn_test_timer_func ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 TYPE_1__* nls ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_release (scalar_t__) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cn_test_init(void)
{
	int err;

	err = cn_add_callback(&cn_test_id, cn_test_name, cn_test_callback);
	if (err)
		goto err_out;
	cn_test_id.val++;
	err = cn_add_callback(&cn_test_id, cn_test_name, cn_test_callback);
	if (err) {
		cn_del_callback(&cn_test_id);
		goto err_out;
	}

	timer_setup(&cn_test_timer, cn_test_timer_func, 0);
	mod_timer(&cn_test_timer, jiffies + msecs_to_jiffies(1000));

	pr_info("initialized with id={%u.%u}\n",
		cn_test_id.idx, cn_test_id.val);

	return 0;

      err_out:
	if (nls && nls->sk_socket)
		sock_release(nls->sk_socket);

	return err;
}