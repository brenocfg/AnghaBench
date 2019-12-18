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
struct wm_adsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  adsp_warn (struct wm_adsp*,char*,unsigned int) ; 

__attribute__((used)) static bool wm_adsp_validate_version(struct wm_adsp *dsp, unsigned int version)
{
	switch (version) {
	case 0:
		adsp_warn(dsp, "Deprecated file format %d\n", version);
		return true;
	case 1:
	case 2:
		return true;
	default:
		return false;
	}
}