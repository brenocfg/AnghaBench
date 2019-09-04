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
typedef  int u16 ;
struct meta_tlvhdr {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int NLA_ALIGN (int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

void *ife_tlv_meta_next(void *skbdata)
{
	struct meta_tlvhdr *tlv = (struct meta_tlvhdr *) skbdata;
	u16 tlvlen = ntohs(tlv->len);

	tlvlen = NLA_ALIGN(tlvlen);

	return skbdata + tlvlen;
}