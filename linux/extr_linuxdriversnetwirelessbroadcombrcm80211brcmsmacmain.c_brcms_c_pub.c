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
struct brcms_pub {int dummy; } ;
struct brcms_c_info {struct brcms_pub* pub; } ;

/* Variables and functions */

struct brcms_pub *brcms_c_pub(struct brcms_c_info *wlc)
{
	return wlc->pub;
}