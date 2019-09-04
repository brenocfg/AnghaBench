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
typedef  size_t u32 ;
struct siu_port {int /*<<< orphan*/  trdat; int /*<<< orphan*/  stfifo; } ;
struct siu_firmware {size_t* yram0; TYPE_1__* spbpar; } ;
struct siu_info {int /*<<< orphan*/  port_id; struct siu_firmware fw; } ;
struct TYPE_2__ {int ab1a; int ab0a; size_t event; int /*<<< orphan*/  trdat; int /*<<< orphan*/  stfifo; } ;

/* Variables and functions */
 struct siu_info* siu_i2s_data ; 

__attribute__((used)) static void siu_dai_spbBselect(struct siu_port *port_info)
{
	struct siu_info *info = siu_i2s_data;
	struct siu_firmware *fw = &info->fw;
	u32 *ydef = fw->yram0;
	u32 idx;

	/* path B use */
	if (!info->port_id)
		idx = 7;		/* portA */
	else
		idx = 8;		/* portB */

	ydef[5] = (fw->spbpar[idx].ab1a << 16) |
		(fw->spbpar[idx].ab0a << 8) | 1;
	ydef[6] = fw->spbpar[idx].event;
	port_info->stfifo |= fw->spbpar[idx].stfifo;
	port_info->trdat |= fw->spbpar[idx].trdat;
}