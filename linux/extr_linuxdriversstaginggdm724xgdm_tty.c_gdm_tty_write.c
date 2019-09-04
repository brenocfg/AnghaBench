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
struct tty_struct {struct gdm* driver_data; } ;
struct gdm {int /*<<< orphan*/  index; TYPE_1__* tty_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  priv_dev; int /*<<< orphan*/  (* send_func ) (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gdm*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GDM_TTY_READY (struct gdm*) ; 
 int /*<<< orphan*/  MUX_TX_MAX_SIZE ; 
 int /*<<< orphan*/  gdm_tty_send_complete ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gdm*) ; 

__attribute__((used)) static int gdm_tty_write(struct tty_struct *tty, const unsigned char *buf,
			 int len)
{
	struct gdm *gdm = tty->driver_data;
	int remain = len;
	int sent_len = 0;
	int sending_len = 0;

	if (!GDM_TTY_READY(gdm))
		return -ENODEV;

	if (!len)
		return 0;

	while (1) {
		sending_len = min(MUX_TX_MAX_SIZE, remain);
		gdm->tty_dev->send_func(gdm->tty_dev->priv_dev,
					(void *)(buf + sent_len),
					sending_len,
					gdm->index,
					gdm_tty_send_complete,
					gdm);
		sent_len += sending_len;
		remain -= sending_len;
		if (remain <= 0)
			break;
	}

	return len;
}