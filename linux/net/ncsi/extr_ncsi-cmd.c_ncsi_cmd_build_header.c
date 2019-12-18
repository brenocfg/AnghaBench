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
struct ncsi_pkt_hdr {scalar_t__* reserved1; int /*<<< orphan*/  length; int /*<<< orphan*/  channel; int /*<<< orphan*/  type; int /*<<< orphan*/  id; scalar_t__ reserved; int /*<<< orphan*/  revision; scalar_t__ mc_id; } ;
struct ncsi_cmd_arg {scalar_t__ payload; int /*<<< orphan*/  channel; int /*<<< orphan*/  package; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ALIGN (scalar_t__,int) ; 
 int /*<<< orphan*/  NCSI_PKT_REVISION ; 
 int /*<<< orphan*/  NCSI_TO_CHANNEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int /*<<< orphan*/  ncsi_calculate_checksum (unsigned char*,scalar_t__) ; 

__attribute__((used)) static void ncsi_cmd_build_header(struct ncsi_pkt_hdr *h,
				  struct ncsi_cmd_arg *nca)
{
	u32 checksum;
	__be32 *pchecksum;

	h->mc_id        = 0;
	h->revision     = NCSI_PKT_REVISION;
	h->reserved     = 0;
	h->id           = nca->id;
	h->type         = nca->type;
	h->channel      = NCSI_TO_CHANNEL(nca->package,
					  nca->channel);
	h->length       = htons(nca->payload);
	h->reserved1[0] = 0;
	h->reserved1[1] = 0;

	/* Fill with calculated checksum */
	checksum = ncsi_calculate_checksum((unsigned char *)h,
					   sizeof(*h) + nca->payload);
	pchecksum = (__be32 *)((void *)h + sizeof(struct ncsi_pkt_hdr) +
		    ALIGN(nca->payload, 4));
	*pchecksum = htonl(checksum);
}