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
struct usb_mixer_interface {struct scarlett2_mixer_data* private_data; } ;
struct scarlett2_ports {int* num; char* dst_descr; } ;
struct scarlett2_mixer_data {TYPE_1__* info; } ;
typedef  int /*<<< orphan*/  s ;
struct TYPE_2__ {struct scarlett2_ports* ports; } ;

/* Variables and functions */
 size_t SCARLETT2_PORT_OUT ; 
 int SCARLETT2_PORT_TYPE_COUNT ; 
 int SNDRV_CTL_ELEM_ID_NAME_MAXLEN ; 
 int scarlett2_add_new_ctl (struct usb_mixer_interface*,int /*<<< orphan*/ *,int,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scarlett2_mux_src_enum_ctl ; 
 int /*<<< orphan*/  snprintf (char*,int,char const* const,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static int scarlett2_add_mux_enums(struct usb_mixer_interface *mixer)
{
	struct scarlett2_mixer_data *private = mixer->private_data;
	const struct scarlett2_ports *ports = private->info->ports;
	int port_type, channel, i;

	for (i = 0, port_type = 0;
	     port_type < SCARLETT2_PORT_TYPE_COUNT;
	     port_type++) {
		for (channel = 0;
		     channel < ports[port_type].num[SCARLETT2_PORT_OUT];
		     channel++, i++) {
			int err;
			char s[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
			const char *const descr = ports[port_type].dst_descr;

			snprintf(s, sizeof(s) - 5, descr, channel + 1);
			strcat(s, " Enum");

			err = scarlett2_add_new_ctl(mixer,
						    &scarlett2_mux_src_enum_ctl,
						    i, 1, s, NULL);
			if (err < 0)
				return err;
		}
	}

	return 0;
}