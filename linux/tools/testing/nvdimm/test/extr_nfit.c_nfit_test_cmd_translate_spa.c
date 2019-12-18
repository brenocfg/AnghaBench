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
struct nvdimm_bus {int dummy; } ;
struct nd_cmd_translate_spa {unsigned int translate_length; int status; int /*<<< orphan*/  num_nvdimms; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ nfit_test_search_spa (struct nvdimm_bus*,struct nd_cmd_translate_spa*) ; 

__attribute__((used)) static int nfit_test_cmd_translate_spa(struct nvdimm_bus *bus,
		struct nd_cmd_translate_spa *spa, unsigned int buf_len)
{
	if (buf_len < spa->translate_length)
		return -EINVAL;

	if (nfit_test_search_spa(bus, spa) < 0 || !spa->num_nvdimms)
		spa->status = 2;

	return 0;
}