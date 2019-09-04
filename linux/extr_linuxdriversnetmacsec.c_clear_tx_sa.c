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
struct macsec_tx_sa {int active; } ;

/* Variables and functions */
 int /*<<< orphan*/  macsec_txsa_put (struct macsec_tx_sa*) ; 

__attribute__((used)) static void clear_tx_sa(struct macsec_tx_sa *tx_sa)
{
	tx_sa->active = false;

	macsec_txsa_put(tx_sa);
}