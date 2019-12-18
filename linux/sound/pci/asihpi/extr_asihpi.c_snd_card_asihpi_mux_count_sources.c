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
typedef  int /*<<< orphan*/  u32 ;
struct snd_kcontrol {int /*<<< orphan*/  private_value; } ;
struct hpi_control {int /*<<< orphan*/  src_node_index; int /*<<< orphan*/  src_node_type; } ;

/* Variables and functions */
 int hpi_multiplexer_query_source (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_card_asihpi_mux_count_sources(struct snd_kcontrol *snd_control)
{
	u32 h_control = snd_control->private_value;
	struct hpi_control hpi_ctl;
	int s, err;
	for (s = 0; s < 32; s++) {
		err = hpi_multiplexer_query_source(h_control, s,
						  &hpi_ctl.
						  src_node_type,
						  &hpi_ctl.
						  src_node_index);
		if (err)
			break;
	}
	return s;
}