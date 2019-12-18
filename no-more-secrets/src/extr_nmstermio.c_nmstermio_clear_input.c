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
 int /*<<< orphan*/  FIONREAD ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  getchar () ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

void nmstermio_clear_input(void) {
	int i;
	
	ioctl(STDIN_FILENO, FIONREAD, &i);

	while (i-- > 0) {
		getchar();
	}
}