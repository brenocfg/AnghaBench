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
typedef  int /*<<< orphan*/  u8 ;
struct parport {int dummy; } ;
struct mts64 {int current_midi_output_port; TYPE_1__* pardev; } ;
struct TYPE_2__ {struct parport* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  mts64_write_command (struct parport*,int) ; 
 int /*<<< orphan*/  mts64_write_data (struct parport*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mts64_write_midi(struct mts64 *mts, u8 c,
			     int midiport)
{
	struct parport *p = mts->pardev->port;

	/* check current midiport */
	if (mts->current_midi_output_port != midiport)
		mts64_write_command(p, midiport);

	/* write midi byte */
	mts64_write_data(p, c);
}