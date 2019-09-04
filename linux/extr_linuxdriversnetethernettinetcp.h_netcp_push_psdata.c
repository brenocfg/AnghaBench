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
typedef  int /*<<< orphan*/  u32 ;
struct netcp_packet {scalar_t__ psdata_len; int /*<<< orphan*/ * psdata; } ;

/* Variables and functions */
 scalar_t__ NETCP_PSDATA_LEN ; 

__attribute__((used)) static inline u32 *netcp_push_psdata(struct netcp_packet *p_info,
				     unsigned int bytes)
{
	u32 *buf;
	unsigned int words;

	if ((bytes & 0x03) != 0)
		return NULL;
	words = bytes >> 2;

	if ((p_info->psdata_len + words) > NETCP_PSDATA_LEN)
		return NULL;

	p_info->psdata_len += words;
	buf = &p_info->psdata[NETCP_PSDATA_LEN - p_info->psdata_len];
	return buf;
}