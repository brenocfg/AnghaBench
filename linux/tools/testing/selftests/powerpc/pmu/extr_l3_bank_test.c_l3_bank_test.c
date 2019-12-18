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
struct TYPE_2__ {scalar_t__ running; scalar_t__ enabled; } ;
struct event {TYPE_1__ result; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int MALLOC_SIZE ; 
 int /*<<< orphan*/  event_close (struct event*) ; 
 int /*<<< orphan*/  event_init (struct event*,int) ; 
 int event_open (struct event*) ; 
 int /*<<< orphan*/  event_read (struct event*) ; 
 int /*<<< orphan*/  event_report (struct event*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 

__attribute__((used)) static int l3_bank_test(void)
{
	struct event event;
	char *p;
	int i;

	p = malloc(MALLOC_SIZE);
	FAIL_IF(!p);

	event_init(&event, 0x84918F);

	FAIL_IF(event_open(&event));

	for (i = 0; i < MALLOC_SIZE; i += 0x10000)
		p[i] = i;

	event_read(&event);
	event_report(&event);

	FAIL_IF(event.result.running == 0);
	FAIL_IF(event.result.enabled == 0);

	event_close(&event);
	free(p);

	return 0;
}