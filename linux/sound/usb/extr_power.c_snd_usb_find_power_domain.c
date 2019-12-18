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
struct usb_host_interface {int /*<<< orphan*/  extralen; int /*<<< orphan*/  extra; } ;
struct uac3_power_domain_descriptor {int bNrEntities; unsigned char* baEntityID; int /*<<< orphan*/  waRecoveryTime2; int /*<<< orphan*/  waRecoveryTime1; int /*<<< orphan*/  bPowerDomainID; } ;
struct snd_usb_power_domain {void* pd_d2d0_rec; void* pd_d1d0_rec; int /*<<< orphan*/  pd_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  UAC3_POWER_DOMAIN ; 
 int /*<<< orphan*/  UAC_VERSION_3 ; 
 int /*<<< orphan*/  kfree (struct snd_usb_power_domain*) ; 
 struct snd_usb_power_domain* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* snd_usb_find_csint_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_usb_validate_audio_desc (void*,int /*<<< orphan*/ ) ; 

struct snd_usb_power_domain *
snd_usb_find_power_domain(struct usb_host_interface *ctrl_iface,
			  unsigned char id)
{
	struct snd_usb_power_domain *pd;
	void *p;

	pd = kzalloc(sizeof(*pd), GFP_KERNEL);
	if (!pd)
		return NULL;

	p = NULL;
	while ((p = snd_usb_find_csint_desc(ctrl_iface->extra,
					    ctrl_iface->extralen,
					    p, UAC3_POWER_DOMAIN)) != NULL) {
		struct uac3_power_domain_descriptor *pd_desc = p;
		int i;

		if (!snd_usb_validate_audio_desc(p, UAC_VERSION_3))
			continue;
		for (i = 0; i < pd_desc->bNrEntities; i++) {
			if (pd_desc->baEntityID[i] == id) {
				pd->pd_id = pd_desc->bPowerDomainID;
				pd->pd_d1d0_rec =
					le16_to_cpu(pd_desc->waRecoveryTime1);
				pd->pd_d2d0_rec =
					le16_to_cpu(pd_desc->waRecoveryTime2);
				return pd;
			}
		}
	}

	kfree(pd);
	return NULL;
}