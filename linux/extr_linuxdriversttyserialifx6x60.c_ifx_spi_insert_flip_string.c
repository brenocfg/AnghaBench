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
struct ifx_spi_device {int /*<<< orphan*/  tty_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_insert_flip_string (int /*<<< orphan*/ *,unsigned char*,size_t) ; 

__attribute__((used)) static void ifx_spi_insert_flip_string(struct ifx_spi_device *ifx_dev,
				    unsigned char *chars, size_t size)
{
	tty_insert_flip_string(&ifx_dev->tty_port, chars, size);
	tty_flip_buffer_push(&ifx_dev->tty_port);
}