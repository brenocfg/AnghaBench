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
struct wmfw_adsp2_sizes {int /*<<< orphan*/  zm; int /*<<< orphan*/  pm; int /*<<< orphan*/  ym; int /*<<< orphan*/  xm; } ;
struct wm_adsp {int dummy; } ;
struct firmware {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  adsp_dbg (struct wm_adsp*,char*,char const* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int wm_adsp2_parse_sizes(struct wm_adsp *dsp,
					 const char * const file,
					 unsigned int pos,
					 const struct firmware *firmware)
{
	const struct wmfw_adsp2_sizes *adsp2_sizes;

	adsp2_sizes = (void *)&firmware->data[pos];

	adsp_dbg(dsp, "%s: %d XM, %d YM %d PM, %d ZM\n", file,
		 le32_to_cpu(adsp2_sizes->xm), le32_to_cpu(adsp2_sizes->ym),
		 le32_to_cpu(adsp2_sizes->pm), le32_to_cpu(adsp2_sizes->zm));

	return pos + sizeof(*adsp2_sizes);
}