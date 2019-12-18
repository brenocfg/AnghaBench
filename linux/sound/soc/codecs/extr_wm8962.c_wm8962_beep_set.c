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
struct wm8962_priv {int /*<<< orphan*/  beep; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EV_SND ; 
 int /*<<< orphan*/  SND_TONE ; 
 struct wm8962_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int kstrtol (char const*,int,long*) ; 

__attribute__((used)) static ssize_t wm8962_beep_set(struct device *dev,
			       struct device_attribute *attr,
			       const char *buf, size_t count)
{
	struct wm8962_priv *wm8962 = dev_get_drvdata(dev);
	long int time;
	int ret;

	ret = kstrtol(buf, 10, &time);
	if (ret != 0)
		return ret;

	input_event(wm8962->beep, EV_SND, SND_TONE, time);

	return count;
}