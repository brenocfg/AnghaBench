#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* values; } ;
typedef  TYPE_1__ ax25_dev ;
struct TYPE_6__ {int rtt; int t1; int t2; int t3; int idle; scalar_t__ window; int /*<<< orphan*/  modulus; scalar_t__ backoff; scalar_t__ paclen; scalar_t__ n2; } ;
typedef  TYPE_2__ ax25_cb ;

/* Variables and functions */
 int /*<<< orphan*/  AX25_EMODULUS ; 
 int /*<<< orphan*/  AX25_MODULUS ; 
 size_t AX25_VALUES_AXDEFMODE ; 
 size_t AX25_VALUES_BACKOFF ; 
 size_t AX25_VALUES_EWINDOW ; 
 size_t AX25_VALUES_IDLE ; 
 size_t AX25_VALUES_N2 ; 
 size_t AX25_VALUES_PACLEN ; 
 size_t AX25_VALUES_T1 ; 
 size_t AX25_VALUES_T2 ; 
 size_t AX25_VALUES_T3 ; 
 size_t AX25_VALUES_WINDOW ; 
 int msecs_to_jiffies (scalar_t__) ; 

__attribute__((used)) static void ax25_fillin_cb_from_dev(ax25_cb *ax25, ax25_dev *ax25_dev)
{
	ax25->rtt     = msecs_to_jiffies(ax25_dev->values[AX25_VALUES_T1]) / 2;
	ax25->t1      = msecs_to_jiffies(ax25_dev->values[AX25_VALUES_T1]);
	ax25->t2      = msecs_to_jiffies(ax25_dev->values[AX25_VALUES_T2]);
	ax25->t3      = msecs_to_jiffies(ax25_dev->values[AX25_VALUES_T3]);
	ax25->n2      = ax25_dev->values[AX25_VALUES_N2];
	ax25->paclen  = ax25_dev->values[AX25_VALUES_PACLEN];
	ax25->idle    = msecs_to_jiffies(ax25_dev->values[AX25_VALUES_IDLE]);
	ax25->backoff = ax25_dev->values[AX25_VALUES_BACKOFF];

	if (ax25_dev->values[AX25_VALUES_AXDEFMODE]) {
		ax25->modulus = AX25_EMODULUS;
		ax25->window  = ax25_dev->values[AX25_VALUES_EWINDOW];
	} else {
		ax25->modulus = AX25_MODULUS;
		ax25->window  = ax25_dev->values[AX25_VALUES_WINDOW];
	}
}