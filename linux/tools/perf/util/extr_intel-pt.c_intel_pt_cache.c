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
struct machine {int dummy; } ;
struct intel_pt_cache_entry {int dummy; } ;
struct dso {struct auxtrace_cache* auxtrace_cache; } ;
struct auxtrace_cache {int dummy; } ;

/* Variables and functions */
 struct auxtrace_cache* auxtrace_cache__new (unsigned int,int,int) ; 
 unsigned int intel_pt_cache_size (struct dso*,struct machine*) ; 

__attribute__((used)) static struct auxtrace_cache *intel_pt_cache(struct dso *dso,
					     struct machine *machine)
{
	struct auxtrace_cache *c;
	unsigned int bits;

	if (dso->auxtrace_cache)
		return dso->auxtrace_cache;

	bits = intel_pt_cache_size(dso, machine);

	/* Ignoring cache creation failure */
	c = auxtrace_cache__new(bits, sizeof(struct intel_pt_cache_entry), 200);

	dso->auxtrace_cache = c;

	return c;
}