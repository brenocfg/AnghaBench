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
struct hdspm {TYPE_1__* midi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dataOut; } ;

/* Variables and functions */
 void hdspm_write (struct hdspm*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void snd_hdspm_midi_write_byte (struct hdspm *hdspm, int id,
					      int val)
{
	/* the hardware already does the relevant bit-mask with 0xff */
	return hdspm_write(hdspm, hdspm->midi[id].dataOut, val);
}