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
struct module {int dummy; } ;
struct bpf_raw_event_map {int dummy; } ;

/* Variables and functions */
 struct module* __module_address (unsigned long) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 

void bpf_put_raw_tracepoint(struct bpf_raw_event_map *btp)
{
	struct module *mod = __module_address((unsigned long)btp);

	if (mod)
		module_put(mod);
}