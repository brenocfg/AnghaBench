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
struct dscc4_dev_priv {scalar_t__ tx_current; scalar_t__ tx_dirty; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int dscc4_tx_done(struct dscc4_dev_priv *dpriv)
{
	return dpriv->tx_current == dpriv->tx_dirty;
}