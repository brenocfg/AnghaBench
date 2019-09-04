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
struct hdac_device {int vendor_id; int revision_id; int type; } ;

/* Variables and functions */
 int snprintf (char*,size_t,char*,int,int,int) ; 

int snd_hdac_codec_modalias(struct hdac_device *codec, char *buf, size_t size)
{
	return snprintf(buf, size, "hdaudio:v%08Xr%08Xa%02X\n",
			codec->vendor_id, codec->revision_id, codec->type);
}