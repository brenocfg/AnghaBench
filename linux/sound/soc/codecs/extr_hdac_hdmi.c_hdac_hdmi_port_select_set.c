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
struct hdac_hdmi_port {int id; TYPE_1__* pin; } ;
struct hdac_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  nid; int /*<<< orphan*/  mst_capable; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_DEVICE_SEL ; 
 int EIO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int hdac_hdmi_get_port_len (struct hdac_device*,int /*<<< orphan*/ ) ; 
 int hdac_hdmi_port_select_get (struct hdac_device*,struct hdac_hdmi_port*) ; 
 int /*<<< orphan*/  snd_hdac_codec_write (struct hdac_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hdac_hdmi_port_select_set(struct hdac_device *hdev,
					struct hdac_hdmi_port *port)
{
	int num_ports;

	if (!port->pin->mst_capable)
		return 0;

	/* AC_PAR_DEVLIST_LEN is 0 based. */
	num_ports = hdac_hdmi_get_port_len(hdev, port->pin->nid);
	if (num_ports < 0)
		return -EIO;
	/*
	 * Device List Length is a 0 based integer value indicating the
	 * number of sink device that a MST Pin Widget can support.
	 */
	if (num_ports + 1  < port->id)
		return 0;

	snd_hdac_codec_write(hdev, port->pin->nid, 0,
			AC_VERB_SET_DEVICE_SEL, port->id);

	if (port->id != hdac_hdmi_port_select_get(hdev, port))
		return -EIO;

	dev_dbg(&hdev->dev, "Selected the port=%d\n", port->id);

	return 0;
}