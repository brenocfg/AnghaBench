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
typedef  scalar_t__ uint ;
typedef  int /*<<< orphan*/  u8 ;
struct brcmf_tlv {int len; scalar_t__ id; } ;

/* Variables and functions */
 int TLV_HDR_LEN ; 

__attribute__((used)) static const struct brcmf_tlv *
brcmf_parse_tlvs(const void *buf, int buflen, uint key)
{
	const struct brcmf_tlv *elt = buf;
	int totlen = buflen;

	/* find tagged parameter */
	while (totlen >= TLV_HDR_LEN) {
		int len = elt->len;

		/* validate remaining totlen */
		if ((elt->id == key) && (totlen >= (len + TLV_HDR_LEN)))
			return elt;

		elt = (struct brcmf_tlv *)((u8 *)elt + (len + TLV_HDR_LEN));
		totlen -= (len + TLV_HDR_LEN);
	}

	return NULL;
}