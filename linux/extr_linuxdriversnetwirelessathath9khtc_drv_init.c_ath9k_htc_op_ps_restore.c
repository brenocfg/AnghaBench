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
struct ath_common {scalar_t__ priv; } ;
struct ath9k_htc_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath9k_htc_ps_restore (struct ath9k_htc_priv*) ; 

__attribute__((used)) static void ath9k_htc_op_ps_restore(struct ath_common *common)
{
	ath9k_htc_ps_restore((struct ath9k_htc_priv *) common->priv);
}