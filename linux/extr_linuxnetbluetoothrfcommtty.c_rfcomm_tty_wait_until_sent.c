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
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct tty_struct*,int) ; 

__attribute__((used)) static void rfcomm_tty_wait_until_sent(struct tty_struct *tty, int timeout)
{
	BT_DBG("tty %p timeout %d", tty, timeout);
}