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
struct db1x_pcmcia_sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCSR_SIGSTAT ; 
 int bcsr_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int db1300_card_inserted(struct db1x_pcmcia_sock *sock)
{
	return bcsr_read(BCSR_SIGSTAT) & (1 << 8);
}