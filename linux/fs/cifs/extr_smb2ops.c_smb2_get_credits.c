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
struct smb2_sync_hdr {int /*<<< orphan*/  CreditRequest; } ;
struct mid_q_entry {scalar_t__ mid_state; scalar_t__ resp_buf; } ;

/* Variables and functions */
 scalar_t__ MID_RESPONSE_MALFORMED ; 
 scalar_t__ MID_RESPONSE_RECEIVED ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
smb2_get_credits(struct mid_q_entry *mid)
{
	struct smb2_sync_hdr *shdr = (struct smb2_sync_hdr *)mid->resp_buf;

	if (mid->mid_state == MID_RESPONSE_RECEIVED
	    || mid->mid_state == MID_RESPONSE_MALFORMED)
		return le16_to_cpu(shdr->CreditRequest);

	return 0;
}