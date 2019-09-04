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
struct sony_laptop_keypress {int /*<<< orphan*/  dev; int /*<<< orphan*/  key; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  kp ;
struct TYPE_2__ {int /*<<< orphan*/  fifo; int /*<<< orphan*/ * jog_dev; int /*<<< orphan*/ * key_dev; int /*<<< orphan*/  release_key_timer; int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int kfifo_out (int /*<<< orphan*/ *,unsigned char*,int) ; 
 TYPE_1__ sony_laptop_input ; 

__attribute__((used)) static void sony_laptop_remove_input(void)
{
	struct sony_laptop_keypress kp = { NULL };

	/* Cleanup only after the last user has gone */
	if (!atomic_dec_and_test(&sony_laptop_input.users))
		return;

	del_timer_sync(&sony_laptop_input.release_key_timer);

	/*
	 * Generate key-up events for remaining keys. Note that we don't
	 * need locking since nobody is adding new events to the kfifo.
	 */
	while (kfifo_out(&sony_laptop_input.fifo,
			 (unsigned char *)&kp, sizeof(kp)) == sizeof(kp)) {
		input_report_key(kp.dev, kp.key, 0);
		input_sync(kp.dev);
	}

	/* destroy input devs */
	input_unregister_device(sony_laptop_input.key_dev);
	sony_laptop_input.key_dev = NULL;

	if (sony_laptop_input.jog_dev) {
		input_unregister_device(sony_laptop_input.jog_dev);
		sony_laptop_input.jog_dev = NULL;
	}

	kfifo_free(&sony_laptop_input.fifo);
}