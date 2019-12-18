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
struct hda_gen_spec {scalar_t__ aamix_mode; int /*<<< orphan*/  have_aamix_ctl; } ;

/* Variables and functions */

__attribute__((used)) static bool aamix_default(struct hda_gen_spec *spec)
{
	return !spec->have_aamix_ctl || spec->aamix_mode;
}