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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ac97_codec_device {int vendor_id; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct ac97_codec_device* to_ac97_device (struct device*) ; 

__attribute__((used)) static ssize_t vendor_id_show(struct device *dev,
			      struct device_attribute *attr, char *buf)
{
	struct ac97_codec_device *codec = to_ac97_device(dev);

	return sprintf(buf, "%08x", codec->vendor_id);
}