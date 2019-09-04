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
 int /*<<< orphan*/  sclp_vt220_port ; 
 int /*<<< orphan*/  tty_insert_flip_string (int /*<<< orphan*/ *,char const*,unsigned int) ; 

__attribute__((used)) static void sclp_vt220_handle_input(const char *buffer, unsigned int count)
{
	tty_insert_flip_string(&sclp_vt220_port, buffer, count);
}