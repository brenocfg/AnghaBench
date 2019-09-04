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
struct pcmcia_socket {int dummy; } ;

/* Variables and functions */
 int at91_cf_set_socket (struct pcmcia_socket*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dead_socket ; 

__attribute__((used)) static int at91_cf_ss_suspend(struct pcmcia_socket *s)
{
	return at91_cf_set_socket(s, &dead_socket);
}