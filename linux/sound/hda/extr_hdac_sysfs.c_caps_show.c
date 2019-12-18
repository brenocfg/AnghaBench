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
struct widget_attribute {int dummy; } ;
struct hdac_device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int get_wcaps (struct hdac_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t caps_show(struct hdac_device *codec, hda_nid_t nid,
			struct widget_attribute *attr, char *buf)
{
	return sprintf(buf, "0x%08x\n", get_wcaps(codec, nid));
}