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
typedef  int u8 ;
struct smp_chan {int /*<<< orphan*/  enc_key_size; int /*<<< orphan*/  tk; int /*<<< orphan*/  ltk; int /*<<< orphan*/  flags; TYPE_1__* conn; } ;
struct hci_conn {scalar_t__ pending_sec_level; int /*<<< orphan*/  dst_type; int /*<<< orphan*/  dst; int /*<<< orphan*/  hdev; } ;
struct TYPE_2__ {struct hci_conn* hcon; } ;

/* Variables and functions */
 scalar_t__ BT_SECURITY_FIPS ; 
 int /*<<< orphan*/  SMP_FLAG_DEBUG_KEY ; 
 int SMP_LTK_P256 ; 
 int SMP_LTK_P256_DEBUG ; 
 int /*<<< orphan*/  hci_add_ltk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sc_add_ltk(struct smp_chan *smp)
{
	struct hci_conn *hcon = smp->conn->hcon;
	u8 key_type, auth;

	if (test_bit(SMP_FLAG_DEBUG_KEY, &smp->flags))
		key_type = SMP_LTK_P256_DEBUG;
	else
		key_type = SMP_LTK_P256;

	if (hcon->pending_sec_level == BT_SECURITY_FIPS)
		auth = 1;
	else
		auth = 0;

	smp->ltk = hci_add_ltk(hcon->hdev, &hcon->dst, hcon->dst_type,
			       key_type, auth, smp->tk, smp->enc_key_size,
			       0, 0);
}