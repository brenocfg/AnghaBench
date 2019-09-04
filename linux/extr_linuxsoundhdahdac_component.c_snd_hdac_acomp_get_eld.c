#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hdac_device {struct hdac_bus* bus; } ;
struct hdac_bus {struct drm_audio_component* audio_component; } ;
struct drm_audio_component {int /*<<< orphan*/  dev; TYPE_2__* ops; TYPE_1__* audio_ops; } ;
typedef  int hda_nid_t ;
struct TYPE_4__ {int (* get_eld ) (int /*<<< orphan*/ ,int,int,int*,char*,int) ;} ;
struct TYPE_3__ {int (* pin2port ) (struct hdac_device*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int stub1 (struct hdac_device*,int) ; 
 int stub2 (int /*<<< orphan*/ ,int,int,int*,char*,int) ; 

int snd_hdac_acomp_get_eld(struct hdac_device *codec, hda_nid_t nid, int dev_id,
			   bool *audio_enabled, char *buffer, int max_bytes)
{
	struct hdac_bus *bus = codec->bus;
	struct drm_audio_component *acomp = bus->audio_component;
	int port, pipe;

	if (!acomp || !acomp->ops || !acomp->ops->get_eld)
		return -ENODEV;

	port = nid;
	if (acomp->audio_ops && acomp->audio_ops->pin2port) {
		port = acomp->audio_ops->pin2port(codec, nid);
		if (port < 0)
			return -EINVAL;
	}
	pipe = dev_id;
	return acomp->ops->get_eld(acomp->dev, port, pipe, audio_enabled,
				   buffer, max_bytes);
}