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
struct tty_port {int /*<<< orphan*/  itty; } ;
struct tty_ldisc {int dummy; } ;

/* Variables and functions */
 struct tty_struct* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_ldisc_deref (struct tty_ldisc*) ; 
 int tty_ldisc_receive_buf (struct tty_ldisc*,unsigned char const*,char*,size_t) ; 
 struct tty_ldisc* tty_ldisc_ref (struct tty_struct*) ; 

__attribute__((used)) static int tty_port_default_receive_buf(struct tty_port *port,
					const unsigned char *p,
					const unsigned char *f, size_t count)
{
	int ret;
	struct tty_struct *tty;
	struct tty_ldisc *disc;

	tty = READ_ONCE(port->itty);
	if (!tty)
		return 0;

	disc = tty_ldisc_ref(tty);
	if (!disc)
		return 0;

	ret = tty_ldisc_receive_buf(disc, p, (char *)f, count);

	tty_ldisc_deref(disc);

	return ret;
}