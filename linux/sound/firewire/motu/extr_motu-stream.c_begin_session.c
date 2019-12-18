#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int channel; } ;
struct TYPE_3__ {int channel; } ;
struct snd_motu {TYPE_2__ tx_resources; TYPE_1__ rx_resources; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int CHANGE_RX_ISOC_COMM_STATE ; 
 int CHANGE_TX_ISOC_COMM_STATE ; 
 int ISOC_COMM_CONTROL_MASK ; 
 int /*<<< orphan*/  ISOC_COMM_CONTROL_OFFSET ; 
 int RX_ISOC_COMM_CHANNEL_SHIFT ; 
 int RX_ISOC_COMM_IS_ACTIVATED ; 
 int TX_ISOC_COMM_CHANNEL_SHIFT ; 
 int TX_ISOC_COMM_IS_ACTIVATED ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int snd_motu_transaction_read (struct snd_motu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int snd_motu_transaction_write (struct snd_motu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int begin_session(struct snd_motu *motu)
{
	__be32 reg;
	u32 data;
	int err;

	// Configure the unit to start isochronous communication.
	err = snd_motu_transaction_read(motu, ISOC_COMM_CONTROL_OFFSET, &reg,
					sizeof(reg));
	if (err < 0)
		return err;
	data = be32_to_cpu(reg) & ~ISOC_COMM_CONTROL_MASK;

	data |= CHANGE_RX_ISOC_COMM_STATE | RX_ISOC_COMM_IS_ACTIVATED |
		(motu->rx_resources.channel << RX_ISOC_COMM_CHANNEL_SHIFT) |
		CHANGE_TX_ISOC_COMM_STATE | TX_ISOC_COMM_IS_ACTIVATED |
		(motu->tx_resources.channel << TX_ISOC_COMM_CHANNEL_SHIFT);

	reg = cpu_to_be32(data);
	return snd_motu_transaction_write(motu, ISOC_COMM_CONTROL_OFFSET, &reg,
					  sizeof(reg));
}