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
struct snd_efw {int dummy; } ;
typedef  int /*<<< orphan*/  param ;
typedef  enum snd_efw_transport_mode { ____Placeholder_snd_efw_transport_mode } snd_efw_transport_mode ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  EFC_CAT_TRANSPORT ; 
 int /*<<< orphan*/  EFC_CMD_TRANSPORT_SET_TX_MODE ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int efw_transaction (struct snd_efw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int snd_efw_command_set_tx_mode(struct snd_efw *efw,
				enum snd_efw_transport_mode mode)
{
	__be32 param = cpu_to_be32(mode);
	return efw_transaction(efw, EFC_CAT_TRANSPORT,
			       EFC_CMD_TRANSPORT_SET_TX_MODE,
			       &param, sizeof(param), NULL, 0);
}