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
typedef  int u16 ;
struct ks_wlan_private {int dummy; } ;

/* Variables and functions */
 int get_byte (struct ks_wlan_private*) ; 

__attribute__((used)) static inline u16 get_word(struct ks_wlan_private *priv)
{
	u16 data;

	data = (get_byte(priv) & 0xff);
	data |= ((get_byte(priv) << 8) & 0xff00);
	return data;
}