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

/* Variables and functions */
 size_t IEEE802154_SCF_KEY_ID_MODE (int /*<<< orphan*/ ) ; 
 int* ieee802154_sechdr_lengths ; 

__attribute__((used)) static int ieee802154_hdr_sechdr_len(u8 sc)
{
	return ieee802154_sechdr_lengths[IEEE802154_SCF_KEY_ID_MODE(sc)];
}