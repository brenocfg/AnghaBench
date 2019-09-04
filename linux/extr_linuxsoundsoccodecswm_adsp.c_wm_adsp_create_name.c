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
struct wm_adsp {char* fwf_name; scalar_t__ name; int /*<<< orphan*/  dev; int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ devm_kasprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* devm_kstrdup (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 char tolower (char) ; 

__attribute__((used)) static int wm_adsp_create_name(struct wm_adsp *dsp)
{
	char *p;

	if (!dsp->name) {
		dsp->name = devm_kasprintf(dsp->dev, GFP_KERNEL, "DSP%d",
					   dsp->num);
		if (!dsp->name)
			return -ENOMEM;
	}

	if (!dsp->fwf_name) {
		p = devm_kstrdup(dsp->dev, dsp->name, GFP_KERNEL);
		if (!p)
			return -ENOMEM;

		dsp->fwf_name = p;
		for (; *p != 0; ++p)
			*p = tolower(*p);
	}

	return 0;
}