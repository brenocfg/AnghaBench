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
 int /*<<< orphan*/  TEMPL ; 
 int /*<<< orphan*/  close (int) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_temp(char *path)
{
	int fd;

	strcpy(path, TEMPL);

	fd = mkstemp(path);
	if (fd < 0) {
		perror("mkstemp failed");
		return -1;
	}

	close(fd);
	return 0;
}