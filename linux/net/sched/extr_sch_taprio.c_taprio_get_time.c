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
struct taprio_sched {int tk_offset; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  KTIME_MAX ; 
#define  TK_OFFS_MAX 128 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_mono_to_any (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ktime_t taprio_get_time(struct taprio_sched *q)
{
	ktime_t mono = ktime_get();

	switch (q->tk_offset) {
	case TK_OFFS_MAX:
		return mono;
	default:
		return ktime_mono_to_any(mono, q->tk_offset);
	}

	return KTIME_MAX;
}