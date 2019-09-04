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
struct ks_wlan_private {unsigned char* rxp; unsigned int rx_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  devio_rec_ind (struct ks_wlan_private*,unsigned char*,unsigned int) ; 
 scalar_t__ get_word (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_event_check (struct ks_wlan_private*) ; 

void hostif_receive(struct ks_wlan_private *priv, unsigned char *p,
		    unsigned int size)
{
	devio_rec_ind(priv, p, size);

	priv->rxp = p;
	priv->rx_size = size;

	if (get_word(priv) == priv->rx_size)
		hostif_event_check(priv);
}