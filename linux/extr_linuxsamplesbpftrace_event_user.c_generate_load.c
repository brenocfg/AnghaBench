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
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ system (char*) ; 

__attribute__((used)) static inline int generate_load(void)
{
	if (system("dd if=/dev/zero of=/dev/null count=5000k status=none") < 0) {
		printf("failed to generate some load with dd: %s\n", strerror(errno));
		return -1;
	}

	return 0;
}