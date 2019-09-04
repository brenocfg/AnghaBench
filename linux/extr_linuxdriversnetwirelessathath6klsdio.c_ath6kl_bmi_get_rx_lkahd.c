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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ath6kl {int dummy; } ;
typedef  int /*<<< orphan*/  rx_word ;

/* Variables and functions */
 int /*<<< orphan*/  BMI_COMMUNICATION_TIMEOUT ; 
 int EINVAL ; 
 int ENDPOINT1 ; 
 int /*<<< orphan*/  HIF_RD_SYNC_BYTE_INC ; 
 int /*<<< orphan*/  RX_LOOKAHEAD_VALID_ADDRESS ; 
 int /*<<< orphan*/  ath6kl_err (char*) ; 
 int ath6kl_sdio_read_write_sync (struct ath6kl*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int ath6kl_bmi_get_rx_lkahd(struct ath6kl *ar)
{
	unsigned long timeout;
	u32 rx_word = 0;
	int ret = 0;

	timeout = jiffies + msecs_to_jiffies(BMI_COMMUNICATION_TIMEOUT);
	while ((time_before(jiffies, timeout)) && !rx_word) {
		ret = ath6kl_sdio_read_write_sync(ar,
					RX_LOOKAHEAD_VALID_ADDRESS,
					(u8 *)&rx_word, sizeof(rx_word),
					HIF_RD_SYNC_BYTE_INC);
		if (ret) {
			ath6kl_err("unable to read RX_LOOKAHEAD_VALID\n");
			return ret;
		}

		 /* all we really want is one bit */
		rx_word &= (1 << ENDPOINT1);
	}

	if (!rx_word) {
		ath6kl_err("bmi_recv_buf FIFO empty\n");
		return -EINVAL;
	}

	return ret;
}