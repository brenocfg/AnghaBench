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
struct smp_chan {int remote_key_dist; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMP_ALLOW_CMD (struct smp_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMP_CMD_ENCRYPT_INFO ; 
 int /*<<< orphan*/  SMP_CMD_IDENT_INFO ; 
 int /*<<< orphan*/  SMP_CMD_SIGN_INFO ; 
 int SMP_DIST_ENC_KEY ; 
 int SMP_DIST_ID_KEY ; 
 int SMP_DIST_SIGN ; 

__attribute__((used)) static void smp_allow_key_dist(struct smp_chan *smp)
{
	/* Allow the first expected phase 3 PDU. The rest of the PDUs
	 * will be allowed in each PDU handler to ensure we receive
	 * them in the correct order.
	 */
	if (smp->remote_key_dist & SMP_DIST_ENC_KEY)
		SMP_ALLOW_CMD(smp, SMP_CMD_ENCRYPT_INFO);
	else if (smp->remote_key_dist & SMP_DIST_ID_KEY)
		SMP_ALLOW_CMD(smp, SMP_CMD_IDENT_INFO);
	else if (smp->remote_key_dist & SMP_DIST_SIGN)
		SMP_ALLOW_CMD(smp, SMP_CMD_SIGN_INFO);
}