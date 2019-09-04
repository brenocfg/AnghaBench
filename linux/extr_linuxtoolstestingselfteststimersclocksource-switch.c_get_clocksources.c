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

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 size_t read (int,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int get_clocksources(char list[][30])
{
	int fd, i;
	size_t size;
	char buf[512];
	char *head, *tmp;

	fd = open("/sys/devices/system/clocksource/clocksource0/available_clocksource", O_RDONLY);

	size = read(fd, buf, 512);

	close(fd);

	for (i = 0; i < 10; i++)
		list[i][0] = '\0';

	head = buf;
	i = 0;
	while (head - buf < size) {
		/* Find the next space */
		for (tmp = head; *tmp != ' '; tmp++) {
			if (*tmp == '\n')
				break;
			if (*tmp == '\0')
				break;
		}
		*tmp = '\0';
		strcpy(list[i], head);
		head = tmp + 1;
		i++;
	}

	return i-1;
}