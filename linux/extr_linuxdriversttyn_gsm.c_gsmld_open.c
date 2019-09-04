#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int receive_room; struct gsm_mux* disc_data; TYPE_1__* ops; } ;
struct gsm_mux {int encoding; } ;
struct TYPE_2__ {int /*<<< orphan*/ * write; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct gsm_mux* gsm_alloc_mux () ; 
 int /*<<< orphan*/  gsm_cleanup_mux (struct gsm_mux*) ; 
 int gsmld_attach_gsm (struct tty_struct*,struct gsm_mux*) ; 
 int /*<<< orphan*/  mux_put (struct gsm_mux*) ; 

__attribute__((used)) static int gsmld_open(struct tty_struct *tty)
{
	struct gsm_mux *gsm;
	int ret;

	if (tty->ops->write == NULL)
		return -EINVAL;

	/* Attach our ldisc data */
	gsm = gsm_alloc_mux();
	if (gsm == NULL)
		return -ENOMEM;

	tty->disc_data = gsm;
	tty->receive_room = 65536;

	/* Attach the initial passive connection */
	gsm->encoding = 1;

	ret = gsmld_attach_gsm(tty, gsm);
	if (ret != 0) {
		gsm_cleanup_mux(gsm);
		mux_put(gsm);
	}
	return ret;
}