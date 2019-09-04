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
struct hdac_hdmi_priv {int dummy; } ;
struct hdac_hdmi_pcm {int /*<<< orphan*/  chmap; } ;
struct hdac_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct hdac_hdmi_pcm* get_hdmi_pcm_from_id (struct hdac_hdmi_priv*,int) ; 
 struct hdac_hdmi_priv* hdev_to_hdmi_priv (struct hdac_device*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdac_hdmi_get_chmap(struct hdac_device *hdev, int pcm_idx,
					unsigned char *chmap)
{
	struct hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	struct hdac_hdmi_pcm *pcm = get_hdmi_pcm_from_id(hdmi, pcm_idx);

	memcpy(chmap, pcm->chmap, ARRAY_SIZE(pcm->chmap));
}