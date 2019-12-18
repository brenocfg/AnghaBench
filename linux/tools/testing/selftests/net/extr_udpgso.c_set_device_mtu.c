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
 int /*<<< orphan*/  __set_device_mtu (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cfg_ifname ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int get_device_mtu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void set_device_mtu(int fd, int mtu)
{
	int val;

	val = get_device_mtu(fd, cfg_ifname);
	fprintf(stderr, "device mtu (orig): %u\n", val);

	__set_device_mtu(fd, cfg_ifname, mtu);
	val = get_device_mtu(fd, cfg_ifname);
	if (val != mtu)
		error(1, 0, "unable to set device mtu to %u\n", val);

	fprintf(stderr, "device mtu (test): %u\n", val);
}