#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ax25_dev ;
struct TYPE_4__ {int rtt; int t1; int t2; int t3; int idle; int /*<<< orphan*/  window; int /*<<< orphan*/  modulus; int /*<<< orphan*/  backoff; int /*<<< orphan*/  paclen; int /*<<< orphan*/  n2; int /*<<< orphan*/ * ax25_dev; } ;
typedef  TYPE_1__ ax25_cb ;

/* Variables and functions */
 scalar_t__ AX25_DEF_AXDEFMODE ; 
 int /*<<< orphan*/  AX25_DEF_BACKOFF ; 
 int /*<<< orphan*/  AX25_DEF_EWINDOW ; 
 int /*<<< orphan*/  AX25_DEF_IDLE ; 
 int /*<<< orphan*/  AX25_DEF_N2 ; 
 int /*<<< orphan*/  AX25_DEF_PACLEN ; 
 int /*<<< orphan*/  AX25_DEF_T1 ; 
 int /*<<< orphan*/  AX25_DEF_T2 ; 
 int /*<<< orphan*/  AX25_DEF_T3 ; 
 int /*<<< orphan*/  AX25_DEF_WINDOW ; 
 int /*<<< orphan*/  AX25_EMODULUS ; 
 int /*<<< orphan*/  AX25_MODULUS ; 
 int /*<<< orphan*/  ax25_fillin_cb_from_dev (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int msecs_to_jiffies (int /*<<< orphan*/ ) ; 

void ax25_fillin_cb(ax25_cb *ax25, ax25_dev *ax25_dev)
{
	ax25->ax25_dev = ax25_dev;

	if (ax25->ax25_dev != NULL) {
		ax25_fillin_cb_from_dev(ax25, ax25_dev);
		return;
	}

	/*
	 * No device, use kernel / AX.25 spec default values
	 */
	ax25->rtt     = msecs_to_jiffies(AX25_DEF_T1) / 2;
	ax25->t1      = msecs_to_jiffies(AX25_DEF_T1);
	ax25->t2      = msecs_to_jiffies(AX25_DEF_T2);
	ax25->t3      = msecs_to_jiffies(AX25_DEF_T3);
	ax25->n2      = AX25_DEF_N2;
	ax25->paclen  = AX25_DEF_PACLEN;
	ax25->idle    = msecs_to_jiffies(AX25_DEF_IDLE);
	ax25->backoff = AX25_DEF_BACKOFF;

	if (AX25_DEF_AXDEFMODE) {
		ax25->modulus = AX25_EMODULUS;
		ax25->window  = AX25_DEF_EWINDOW;
	} else {
		ax25->modulus = AX25_MODULUS;
		ax25->window  = AX25_DEF_WINDOW;
	}
}