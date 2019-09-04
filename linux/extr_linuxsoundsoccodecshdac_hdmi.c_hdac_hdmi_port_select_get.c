#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hdac_hdmi_port {TYPE_1__* pin; } ;
struct hdac_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_GET_DEVICE_SEL ; 
 int snd_hdac_codec_read (struct hdac_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdac_hdmi_port_select_get(struct hdac_device *hdev,
					struct hdac_hdmi_port *port)
{
	return snd_hdac_codec_read(hdev, port->pin->nid,
				0, AC_VERB_GET_DEVICE_SEL, 0);
}