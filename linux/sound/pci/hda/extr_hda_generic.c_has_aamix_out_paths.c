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
struct hda_gen_spec {scalar_t__* aamix_out_paths; } ;

/* Variables and functions */

__attribute__((used)) static inline bool has_aamix_out_paths(struct hda_gen_spec *spec)
{
	return spec->aamix_out_paths[0] || spec->aamix_out_paths[1] ||
		spec->aamix_out_paths[2];
}