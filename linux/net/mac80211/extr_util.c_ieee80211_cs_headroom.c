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
struct ieee80211_local {int dummy; } ;
struct ieee80211_cipher_scheme {int hdr_len; } ;
struct cfg80211_crypto_settings {int n_ciphers_pairwise; int /*<<< orphan*/  cipher_group; int /*<<< orphan*/ * ciphers_pairwise; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int IEEE80211_ENCRYPT_HEADROOM ; 
 struct ieee80211_cipher_scheme* ieee80211_cs_get (struct ieee80211_local*,int /*<<< orphan*/ ,int) ; 

int ieee80211_cs_headroom(struct ieee80211_local *local,
			  struct cfg80211_crypto_settings *crypto,
			  enum nl80211_iftype iftype)
{
	const struct ieee80211_cipher_scheme *cs;
	int headroom = IEEE80211_ENCRYPT_HEADROOM;
	int i;

	for (i = 0; i < crypto->n_ciphers_pairwise; i++) {
		cs = ieee80211_cs_get(local, crypto->ciphers_pairwise[i],
				      iftype);

		if (cs && headroom < cs->hdr_len)
			headroom = cs->hdr_len;
	}

	cs = ieee80211_cs_get(local, crypto->cipher_group, iftype);
	if (cs && headroom < cs->hdr_len)
		headroom = cs->hdr_len;

	return headroom;
}