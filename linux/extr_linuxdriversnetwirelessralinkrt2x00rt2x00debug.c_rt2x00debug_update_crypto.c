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
struct rxdone_entry_desc {int cipher; int cipher_status; } ;
struct rt2x00debug_intf {TYPE_1__* crypto_stats; } ;
struct rt2x00_dev {struct rt2x00debug_intf* debugfs_intf; } ;
typedef  enum rx_crypto { ____Placeholder_rx_crypto } rx_crypto ;
typedef  enum cipher { ____Placeholder_cipher } cipher ;
struct TYPE_2__ {int success; int icv_error; int mic_error; int key_error; } ;

/* Variables and functions */
 int CIPHER_MAX ; 
 int CIPHER_NONE ; 
 int CIPHER_TKIP ; 
 int CIPHER_TKIP_NO_MIC ; 
 int RX_CRYPTO_FAIL_ICV ; 
 int RX_CRYPTO_FAIL_KEY ; 
 int RX_CRYPTO_FAIL_MIC ; 
 int RX_CRYPTO_SUCCESS ; 

void rt2x00debug_update_crypto(struct rt2x00_dev *rt2x00dev,
			       struct rxdone_entry_desc *rxdesc)
{
	struct rt2x00debug_intf *intf = rt2x00dev->debugfs_intf;
	enum cipher cipher = rxdesc->cipher;
	enum rx_crypto status = rxdesc->cipher_status;

	if (cipher == CIPHER_TKIP_NO_MIC)
		cipher = CIPHER_TKIP;
	if (cipher == CIPHER_NONE || cipher >= CIPHER_MAX)
		return;

	/* Remove CIPHER_NONE index */
	cipher--;

	intf->crypto_stats[cipher].success += (status == RX_CRYPTO_SUCCESS);
	intf->crypto_stats[cipher].icv_error += (status == RX_CRYPTO_FAIL_ICV);
	intf->crypto_stats[cipher].mic_error += (status == RX_CRYPTO_FAIL_MIC);
	intf->crypto_stats[cipher].key_error += (status == RX_CRYPTO_FAIL_KEY);
}