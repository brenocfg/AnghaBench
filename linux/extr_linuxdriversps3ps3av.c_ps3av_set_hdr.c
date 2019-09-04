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
typedef  scalar_t__ u16 ;
struct ps3av_send_hdr {int /*<<< orphan*/  cid; scalar_t__ size; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 scalar_t__ PS3AV_HDR_SIZE ; 
 int /*<<< orphan*/  PS3AV_VERSION ; 

void ps3av_set_hdr(u32 cid, u16 size, struct ps3av_send_hdr *hdr)
{
	hdr->version = PS3AV_VERSION;
	hdr->size = size - PS3AV_HDR_SIZE;
	hdr->cid = cid;
}