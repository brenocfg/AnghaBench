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
struct ath_hw {int dummy; } ;
struct ath9k_htc_priv {struct ath_hw* ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath9k_htc_calcrxfilter (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_hw_setmcastfilter (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_setrxfilter (struct ath_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath9k_htc_opmode_init(struct ath9k_htc_priv *priv)
{
	struct ath_hw *ah = priv->ah;
	u32 rfilt, mfilt[2];

	/* configure rx filter */
	rfilt = ath9k_htc_calcrxfilter(priv);
	ath9k_hw_setrxfilter(ah, rfilt);

	/* calculate and install multicast filter */
	mfilt[0] = mfilt[1] = ~0;
	ath9k_hw_setmcastfilter(ah, mfilt[0], mfilt[1]);
}