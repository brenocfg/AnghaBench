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
typedef  scalar_t__ u8 ;
struct p80211pstrd {int /*<<< orphan*/  data; scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,int) ; 

void prism2mgmt_bytearea2pstr(u8 *bytearea, struct p80211pstrd *pstr, int len)
{
	pstr->len = (u8)len;
	memcpy(pstr->data, bytearea, len);
}