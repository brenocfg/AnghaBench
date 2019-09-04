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
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43_radio_2057_init_post (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_radio_2057_init_pre (struct b43_wldev*) ; 
 int /*<<< orphan*/  r2057_upload_inittabs (struct b43_wldev*) ; 

__attribute__((used)) static void b43_radio_2057_init(struct b43_wldev *dev)
{
	b43_radio_2057_init_pre(dev);
	r2057_upload_inittabs(dev);
	b43_radio_2057_init_post(dev);
}