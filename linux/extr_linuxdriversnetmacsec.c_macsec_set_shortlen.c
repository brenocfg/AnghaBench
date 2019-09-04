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
struct macsec_eth_header {size_t short_length; } ;

/* Variables and functions */
 size_t MIN_NON_SHORT_LEN ; 

__attribute__((used)) static void macsec_set_shortlen(struct macsec_eth_header *h, size_t data_len)
{
	if (data_len < MIN_NON_SHORT_LEN)
		h->short_length = data_len;
}