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
struct libipw_network {scalar_t__ ssid_len; scalar_t__ channel; int /*<<< orphan*/  ssid; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 scalar_t__ ether_addr_equal_64bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline int is_same_network(struct libipw_network *src,
				  struct libipw_network *dst)
{
	/* A network is only a duplicate if the channel, BSSID, and ESSID
	 * all match.  We treat all <hidden> with the same BSSID and channel
	 * as one network */
	return ((src->ssid_len == dst->ssid_len) &&
		(src->channel == dst->channel) &&
		ether_addr_equal_64bits(src->bssid, dst->bssid) &&
		!memcmp(src->ssid, dst->ssid, src->ssid_len));
}