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
struct sk_buff {int dummy; } ;
struct mac802154_llsec_key {int dummy; } ;
struct mac802154_llsec {int dummy; } ;
struct TYPE_2__ {scalar_t__ level; } ;
struct ieee802154_hdr {TYPE_1__ sec; } ;

/* Variables and functions */
 scalar_t__ IEEE802154_SCF_SECLEVEL_ENC ; 
 int llsec_do_encrypt_auth (struct sk_buff*,struct mac802154_llsec const*,struct ieee802154_hdr const*,struct mac802154_llsec_key*) ; 
 int llsec_do_encrypt_unauth (struct sk_buff*,struct mac802154_llsec const*,struct ieee802154_hdr const*,struct mac802154_llsec_key*) ; 

__attribute__((used)) static int llsec_do_encrypt(struct sk_buff *skb,
			    const struct mac802154_llsec *sec,
			    const struct ieee802154_hdr *hdr,
			    struct mac802154_llsec_key *key)
{
	if (hdr->sec.level == IEEE802154_SCF_SECLEVEL_ENC)
		return llsec_do_encrypt_unauth(skb, sec, hdr, key);
	else
		return llsec_do_encrypt_auth(skb, sec, hdr, key);
}