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
struct xlgmac_pdata {int dummy; } ;

/* Variables and functions */
 int xlgmac_alloc_channels (struct xlgmac_pdata*) ; 
 int xlgmac_alloc_rings (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  xlgmac_free_channels_and_rings (struct xlgmac_pdata*) ; 

__attribute__((used)) static int xlgmac_alloc_channels_and_rings(struct xlgmac_pdata *pdata)
{
	int ret;

	ret = xlgmac_alloc_channels(pdata);
	if (ret)
		goto err_alloc;

	ret = xlgmac_alloc_rings(pdata);
	if (ret)
		goto err_alloc;

	return 0;

err_alloc:
	xlgmac_free_channels_and_rings(pdata);

	return ret;
}