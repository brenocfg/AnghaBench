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
struct usbhs_priv {int dummy; } ;
struct usbhs_mod_info {struct usbhs_mod* curt; struct usbhs_mod** mod; } ;
struct usbhs_mod {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  USBHS_GADGET 129 
#define  USBHS_HOST 128 
 struct usbhs_mod_info* usbhs_priv_to_modinfo (struct usbhs_priv*) ; 

int usbhs_mod_change(struct usbhs_priv *priv, int id)
{
	struct usbhs_mod_info *info = usbhs_priv_to_modinfo(priv);
	struct usbhs_mod *mod = NULL;
	int ret = 0;

	/* id < 0 mean no current */
	switch (id) {
	case USBHS_HOST:
	case USBHS_GADGET:
		mod = info->mod[id];
		break;
	default:
		ret = -EINVAL;
	}
	info->curt = mod;

	return ret;
}