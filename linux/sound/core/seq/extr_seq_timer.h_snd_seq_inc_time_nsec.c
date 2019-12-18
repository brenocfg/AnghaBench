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
struct TYPE_4__ {unsigned long tv_nsec; } ;
typedef  TYPE_1__ snd_seq_real_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  snd_seq_sanity_real_time (TYPE_1__*) ; 

__attribute__((used)) static inline void snd_seq_inc_time_nsec(snd_seq_real_time_t *tm, unsigned long nsec)
{
	tm->tv_nsec  += nsec;
	snd_seq_sanity_real_time(tm);
}