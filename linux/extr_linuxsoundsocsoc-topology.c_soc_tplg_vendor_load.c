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
struct soc_tplg {scalar_t__ pass; } ;
struct snd_soc_tplg_hdr {int dummy; } ;

/* Variables and functions */
 scalar_t__ SOC_TPLG_PASS_VENDOR ; 
 int soc_tplg_vendor_load_ (struct soc_tplg*,struct snd_soc_tplg_hdr*) ; 

__attribute__((used)) static int soc_tplg_vendor_load(struct soc_tplg *tplg,
	struct snd_soc_tplg_hdr *hdr)
{
	if (tplg->pass != SOC_TPLG_PASS_VENDOR)
		return 0;

	return soc_tplg_vendor_load_(tplg, hdr);
}