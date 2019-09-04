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
typedef  scalar_t__ u8 ;
struct nfc_llcp_sock {int /*<<< orphan*/  ssap; } ;
struct nfc_llcp_local {unsigned long local_wks; unsigned long local_sdp; unsigned long local_sap; int /*<<< orphan*/  sdp_lock; int /*<<< orphan*/ * local_sdp_cnt; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 scalar_t__ LLCP_LOCAL_NUM_SAP ; 
 scalar_t__ LLCP_MAX_SAP ; 
 int /*<<< orphan*/  LLCP_SAP_SDP ; 
 int /*<<< orphan*/  LLCP_SDP_UNBOUND ; 
 scalar_t__ LLCP_WKS_NUM_SAP ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nfc_llcp_sock* nfc_llcp_sock_get (struct nfc_llcp_local*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_llcp_sock_put (struct nfc_llcp_sock*) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 

void nfc_llcp_put_ssap(struct nfc_llcp_local *local, u8 ssap)
{
	u8 local_ssap;
	unsigned long *sdp;

	if (ssap < LLCP_WKS_NUM_SAP) {
		local_ssap = ssap;
		sdp = &local->local_wks;
	} else if (ssap < LLCP_LOCAL_NUM_SAP) {
		atomic_t *client_cnt;

		local_ssap = ssap - LLCP_WKS_NUM_SAP;
		sdp = &local->local_sdp;
		client_cnt = &local->local_sdp_cnt[local_ssap];

		pr_debug("%d clients\n", atomic_read(client_cnt));

		mutex_lock(&local->sdp_lock);

		if (atomic_dec_and_test(client_cnt)) {
			struct nfc_llcp_sock *l_sock;

			pr_debug("No more clients for SAP %d\n", ssap);

			clear_bit(local_ssap, sdp);

			/* Find the listening sock and set it back to UNBOUND */
			l_sock = nfc_llcp_sock_get(local, ssap, LLCP_SAP_SDP);
			if (l_sock) {
				l_sock->ssap = LLCP_SDP_UNBOUND;
				nfc_llcp_sock_put(l_sock);
			}
		}

		mutex_unlock(&local->sdp_lock);

		return;
	} else if (ssap < LLCP_MAX_SAP) {
		local_ssap = ssap - LLCP_LOCAL_NUM_SAP;
		sdp = &local->local_sap;
	} else {
		return;
	}

	mutex_lock(&local->sdp_lock);

	clear_bit(local_ssap, sdp);

	mutex_unlock(&local->sdp_lock);
}