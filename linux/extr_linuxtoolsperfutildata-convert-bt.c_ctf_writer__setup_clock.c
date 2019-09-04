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
struct ctf_writer {struct bt_ctf_clock* clock; } ;
struct bt_ctf_clock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bt_ctf_clock_set_description (struct bt_ctf_clock*,char*) ; 
 scalar_t__ bt_ctf_clock_set_frequency (struct bt_ctf_clock*,int) ; 
 scalar_t__ bt_ctf_clock_set_is_absolute (struct bt_ctf_clock*,int /*<<< orphan*/ ) ; 
 scalar_t__ bt_ctf_clock_set_offset (struct bt_ctf_clock*,int /*<<< orphan*/ ) ; 
 scalar_t__ bt_ctf_clock_set_offset_s (struct bt_ctf_clock*,int /*<<< orphan*/ ) ; 
 scalar_t__ bt_ctf_clock_set_precision (struct bt_ctf_clock*,int) ; 

__attribute__((used)) static int ctf_writer__setup_clock(struct ctf_writer *cw)
{
	struct bt_ctf_clock *clock = cw->clock;

	bt_ctf_clock_set_description(clock, "perf clock");

#define SET(__n, __v)				\
do {						\
	if (bt_ctf_clock_set_##__n(clock, __v))	\
		return -1;			\
} while (0)

	SET(frequency,   1000000000);
	SET(offset_s,    0);
	SET(offset,      0);
	SET(precision,   10);
	SET(is_absolute, 0);

#undef SET
	return 0;
}