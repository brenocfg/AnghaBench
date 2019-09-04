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
 int /*<<< orphan*/  HOST_CTRL_IO (unsigned int) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_host_mode_unsafe(unsigned io_base)
{
	outb(0x0, HOST_CTRL_IO(io_base));
}