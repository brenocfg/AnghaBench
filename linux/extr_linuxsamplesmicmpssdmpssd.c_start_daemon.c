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
struct mic_info {int /*<<< orphan*/  name; int /*<<< orphan*/  init_thread; struct mic_info* next; } ;
struct TYPE_2__ {struct mic_info* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_mic ; 
 TYPE_1__ mic_list ; 
 int /*<<< orphan*/  mpsslog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mic_info*) ; 
 int /*<<< orphan*/  set_mic_boot_params (struct mic_info*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static void
start_daemon(void)
{
	struct mic_info *mic;
	int err;

	for (mic = mic_list.next; mic; mic = mic->next) {
		set_mic_boot_params(mic);
		err = pthread_create(&mic->init_thread, NULL, init_mic, mic);
		if (err)
			mpsslog("%s init_mic pthread_create failed %s\n",
				mic->name, strerror(err));
	}

	while (1)
		sleep(60);
}