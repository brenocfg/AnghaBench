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
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 scalar_t__ IEEE802154_SCF_SECLEVEL_ENC ; 
 int llsec_do_decrypt_auth (struct sk_buff*,struct mac802154_llsec const*,struct ieee802154_hdr const*,struct mac802154_llsec_key*,int /*<<< orphan*/ ) ; 
 int llsec_do_decrypt_unauth (struct sk_buff*,struct mac802154_llsec const*,struct ieee802154_hdr const*,struct mac802154_llsec_key*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
llsec_do_decrypt(struct sk_buff *skb, const struct mac802154_llsec *sec,
		 const struct ieee802154_hdr *hdr,
		 struct mac802154_llsec_key *key, __le64 dev_addr)
{
	if (hdr->sec.level == IEEE802154_SCF_SECLEVEL_ENC)
		return llsec_do_decrypt_unauth(skb, sec, hdr, key, dev_addr);
	else
		return llsec_do_decrypt_auth(skb, sec, hdr, key, dev_addr);
}