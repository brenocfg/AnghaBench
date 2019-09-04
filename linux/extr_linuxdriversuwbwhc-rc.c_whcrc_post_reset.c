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
struct whcrc {struct uwb_rc* uwb_rc; } ;
struct uwb_rc {int dummy; } ;
struct umc_dev {int dummy; } ;

/* Variables and functions */
 struct whcrc* umc_get_drvdata (struct umc_dev*) ; 
 int uwb_rc_post_reset (struct uwb_rc*) ; 

__attribute__((used)) static int whcrc_post_reset(struct umc_dev *umc)
{
	struct whcrc *whcrc = umc_get_drvdata(umc);
	struct uwb_rc *uwb_rc = whcrc->uwb_rc;

	return uwb_rc_post_reset(uwb_rc);
}