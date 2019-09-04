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
struct brcmf_if {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcmf_err (char*,int) ; 
 int brcmf_fil_iovar_data_set (struct brcmf_if*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int brcmf_fil_iovar_int_set (struct brcmf_if*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmf_pno_clean(struct brcmf_if *ifp)
{
	int ret;

	/* Disable pfn */
	ret = brcmf_fil_iovar_int_set(ifp, "pfn", 0);
	if (ret == 0) {
		/* clear pfn */
		ret = brcmf_fil_iovar_data_set(ifp, "pfnclear", NULL, 0);
	}
	if (ret < 0)
		brcmf_err("failed code %d\n", ret);

	return ret;
}