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
struct TYPE_4__ {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
typedef  TYPE_1__ snd_seq_real_time_t ;

/* Variables and functions */

__attribute__((used)) static inline int snd_seq_compare_real_time(snd_seq_real_time_t *a, snd_seq_real_time_t *b)
{
	/* compare real time */
	if (a->tv_sec > b->tv_sec)
		return 1;
	if ((a->tv_sec == b->tv_sec) && (a->tv_nsec >= b->tv_nsec))
		return 1;
	return 0;
}