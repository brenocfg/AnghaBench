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
struct ieee802_11_elems {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee802_11_parse_elems_crc (int /*<<< orphan*/  const*,size_t,int,struct ieee802_11_elems*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ieee802_11_parse_elems(const u8 *start, size_t len,
					  bool action,
					  struct ieee802_11_elems *elems,
					  u8 *transmitter_bssid,
					  u8 *bss_bssid)
{
	ieee802_11_parse_elems_crc(start, len, action, elems, 0, 0,
				   transmitter_bssid, bss_bssid);
}