#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 char* get_tracing_file (char*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  put_events_file (char*) ; 

DIR *tracing_events__opendir(void)
{
	DIR *dir = NULL;
	char *path = get_tracing_file("events");

	if (path) {
		dir = opendir(path);
		put_events_file(path);
	}

	return dir;
}