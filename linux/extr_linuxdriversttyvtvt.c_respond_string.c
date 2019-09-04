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
struct tty_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,char const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_schedule_flip (struct tty_port*) ; 

__attribute__((used)) static void respond_string(const char *p, struct tty_port *port)
{
	while (*p) {
		tty_insert_flip_char(port, *p, 0);
		p++;
	}
	tty_schedule_flip(port);
}