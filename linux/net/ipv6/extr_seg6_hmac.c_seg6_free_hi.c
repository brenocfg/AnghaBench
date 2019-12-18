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
struct seg6_hmac_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  seg6_hinfo_release (struct seg6_hmac_info*) ; 

__attribute__((used)) static void seg6_free_hi(void *ptr, void *arg)
{
	struct seg6_hmac_info *hinfo = (struct seg6_hmac_info *)ptr;

	if (hinfo)
		seg6_hinfo_release(hinfo);
}