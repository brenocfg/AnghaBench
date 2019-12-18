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
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ getit (int,char const**,int,char*) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*) ; 
 int /*<<< orphan*/  stdout ; 

void newer(int argc, const char *argv[])
{
	if (getit(argc, argv, -1, "w")) {
		printf("Local file \"%s\" is newer than remote file \"%s\"\n",
			argv[1], argv[2]);
		(void) fflush(stdout);
	}
}