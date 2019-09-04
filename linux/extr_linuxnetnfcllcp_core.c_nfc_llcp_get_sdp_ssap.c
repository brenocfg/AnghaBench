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
typedef  int u8 ;
struct nfc_llcp_sock {scalar_t__ service_name_len; int ssap; int /*<<< orphan*/ * service_name; } ;
struct nfc_llcp_local {int local_wks; int /*<<< orphan*/  sdp_lock; } ;

/* Variables and functions */
 int BIT (int) ; 
 int LLCP_SAP_MAX ; 
 int LLCP_SDP_UNBOUND ; 
 int LLCP_WKS_NUM_SAP ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nfc_llcp_sock_from_sn (struct nfc_llcp_local*,int /*<<< orphan*/ *,scalar_t__) ; 
 int nfc_llcp_wks_sap (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  set_bit (int,int*) ; 
 int /*<<< orphan*/  test_bit (int,int*) ; 

u8 nfc_llcp_get_sdp_ssap(struct nfc_llcp_local *local,
			 struct nfc_llcp_sock *sock)
{
	mutex_lock(&local->sdp_lock);

	if (sock->service_name != NULL && sock->service_name_len > 0) {
		int ssap = nfc_llcp_wks_sap(sock->service_name,
					    sock->service_name_len);

		if (ssap > 0) {
			pr_debug("WKS %d\n", ssap);

			/* This is a WKS, let's check if it's free */
			if (local->local_wks & BIT(ssap)) {
				mutex_unlock(&local->sdp_lock);

				return LLCP_SAP_MAX;
			}

			set_bit(ssap, &local->local_wks);
			mutex_unlock(&local->sdp_lock);

			return ssap;
		}

		/*
		 * Check if there already is a non WKS socket bound
		 * to this service name.
		 */
		if (nfc_llcp_sock_from_sn(local, sock->service_name,
					  sock->service_name_len) != NULL) {
			mutex_unlock(&local->sdp_lock);

			return LLCP_SAP_MAX;
		}

		mutex_unlock(&local->sdp_lock);

		return LLCP_SDP_UNBOUND;

	} else if (sock->ssap != 0 && sock->ssap < LLCP_WKS_NUM_SAP) {
		if (!test_bit(sock->ssap, &local->local_wks)) {
			set_bit(sock->ssap, &local->local_wks);
			mutex_unlock(&local->sdp_lock);

			return sock->ssap;
		}
	}

	mutex_unlock(&local->sdp_lock);

	return LLCP_SAP_MAX;
}