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
struct TYPE_2__ {int /*<<< orphan*/  dataIn; } ;

/* Variables and functions */
 unsigned char hdspm_read (struct hdspm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned char snd_hdspm_midi_read_byte (struct hdspm *hdspm,
						      int id)
{
	/* the hardware already does the relevant bit-mask with 0xff */
	return hdspm_read(hdspm, hdspm->midi[id].dataIn);
}