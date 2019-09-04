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
struct spk_synth {int alive; } ;

/* Variables and functions */
 int spk_ttyio_initialise_ldisc (struct spk_synth*) ; 
 struct spk_synth* spk_ttyio_synth ; 

int spk_ttyio_synth_probe(struct spk_synth *synth)
{
	int rv = spk_ttyio_initialise_ldisc(synth);

	if (rv)
		return rv;

	synth->alive = 1;
	spk_ttyio_synth = synth;

	return 0;
}