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
struct hdmi_codec_priv {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_JACK_LINEOUT ; 
 struct hdmi_codec_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  hdmi_codec_jack_report (struct hdmi_codec_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void plugged_cb(struct device *dev, bool plugged)
{
	struct hdmi_codec_priv *hcp = dev_get_drvdata(dev);

	if (plugged)
		hdmi_codec_jack_report(hcp, SND_JACK_LINEOUT);
	else
		hdmi_codec_jack_report(hcp, 0);
}