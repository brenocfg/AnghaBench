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
 int __cmd_probe (int,char const**) ; 
 int /*<<< orphan*/  cleanup_params () ; 
 int init_params () ; 

int cmd_probe(int argc, const char **argv)
{
	int ret;

	ret = init_params();
	if (!ret) {
		ret = __cmd_probe(argc, argv);
		cleanup_params();
	}

	return ret < 0 ? ret : 0;
}