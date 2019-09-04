#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ type; int len; } ;
struct sr6_tlv_hmac {TYPE_1__ tlvhdr; } ;
struct ipv6_sr_hdr {int hdrlen; int first_segment; } ;

/* Variables and functions */
 scalar_t__ SR6_TLV_HMAC ; 
 int /*<<< orphan*/  sr_has_hmac (struct ipv6_sr_hdr*) ; 

__attribute__((used)) static struct sr6_tlv_hmac *seg6_get_tlv_hmac(struct ipv6_sr_hdr *srh)
{
	struct sr6_tlv_hmac *tlv;

	if (srh->hdrlen < (srh->first_segment + 1) * 2 + 5)
		return NULL;

	if (!sr_has_hmac(srh))
		return NULL;

	tlv = (struct sr6_tlv_hmac *)
	      ((char *)srh + ((srh->hdrlen + 1) << 3) - 40);

	if (tlv->tlvhdr.type != SR6_TLV_HMAC || tlv->tlvhdr.len != 38)
		return NULL;

	return tlv;
}