#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct special_params {int is1814; } ;
struct TYPE_5__ {void* context; } ;
struct TYPE_4__ {void* context; } ;
struct snd_bebob {int midi_input_ports; int midi_output_ports; int /*<<< orphan*/  mutex; TYPE_3__* unit; TYPE_2__ tx_stream; TYPE_1__ rx_stream; void* maudio_special_quirk; } ;
struct TYPE_6__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int add_special_controls (struct snd_bebob*) ; 
 int avc_maudio_set_special_clk (struct snd_bebob*,int,int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct special_params* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  special_stream_formation_set (struct snd_bebob*) ; 

int
snd_bebob_maudio_special_discover(struct snd_bebob *bebob, bool is1814)
{
	struct special_params *params;
	int err;

	params = kzalloc(sizeof(struct special_params), GFP_KERNEL);
	if (params == NULL)
		return -ENOMEM;

	mutex_lock(&bebob->mutex);

	bebob->maudio_special_quirk = (void *)params;
	params->is1814 = is1814;

	/* initialize these parameters because driver is not allowed to ask */
	bebob->rx_stream.context = ERR_PTR(-1);
	bebob->tx_stream.context = ERR_PTR(-1);
	err = avc_maudio_set_special_clk(bebob, 0x03, 0x00, 0x00, 0x00);
	if (err < 0) {
		dev_err(&bebob->unit->device,
			"fail to initialize clock params: %d\n", err);
		goto end;
	}

	err = add_special_controls(bebob);
	if (err < 0)
		goto end;

	special_stream_formation_set(bebob);

	if (params->is1814) {
		bebob->midi_input_ports = 1;
		bebob->midi_output_ports = 1;
	} else {
		bebob->midi_input_ports = 2;
		bebob->midi_output_ports = 2;
	}
end:
	mutex_unlock(&bebob->mutex);
	return err;
}