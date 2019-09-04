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
typedef  int u32 ;
struct rtl_halmac_indicator {int dummy; } ;
struct rtl_halmac {struct rtl_halmac_indicator* indicator; scalar_t__ send_general_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HALMAC_FEATURE_ALL ; 
 struct rtl_halmac_indicator* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_priv(struct rtl_halmac *halmac)
{
	struct rtl_halmac_indicator *indicator;
	u32 count, size;

	halmac->send_general_info = 0;

	count = HALMAC_FEATURE_ALL + 1;
	size = sizeof(*indicator) * count;
	indicator = kzalloc(size, GFP_KERNEL);
	if (!indicator)
		return -1;
	halmac->indicator = indicator;

	return 0;
}