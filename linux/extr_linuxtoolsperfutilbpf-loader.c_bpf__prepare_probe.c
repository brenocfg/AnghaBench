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
struct TYPE_2__ {int /*<<< orphan*/  max_probes; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_PROBES ; 
 int init_probe_symbol_maps (int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 TYPE_1__ probe_conf ; 

__attribute__((used)) static int bpf__prepare_probe(void)
{
	static int err = 0;
	static bool initialized = false;

	/*
	 * Make err static, so if init failed the first, bpf__prepare_probe()
	 * fails each time without calling init_probe_symbol_maps multiple
	 * times.
	 */
	if (initialized)
		return err;

	initialized = true;
	err = init_probe_symbol_maps(false);
	if (err < 0)
		pr_debug("Failed to init_probe_symbol_maps\n");
	probe_conf.max_probes = MAX_PROBES;
	return err;
}