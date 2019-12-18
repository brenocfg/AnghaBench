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
struct cs42l56_private {int /*<<< orphan*/  beep; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EV_SND ; 
 int /*<<< orphan*/  SND_TONE ; 
 struct cs42l56_private* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int kstrtol (char const*,int,long*) ; 

__attribute__((used)) static ssize_t cs42l56_beep_set(struct device *dev,
			       struct device_attribute *attr,
			       const char *buf, size_t count)
{
	struct cs42l56_private *cs42l56 = dev_get_drvdata(dev);
	long int time;
	int ret;

	ret = kstrtol(buf, 10, &time);
	if (ret != 0)
		return ret;

	input_event(cs42l56->beep, EV_SND, SND_TONE, time);

	return count;
}