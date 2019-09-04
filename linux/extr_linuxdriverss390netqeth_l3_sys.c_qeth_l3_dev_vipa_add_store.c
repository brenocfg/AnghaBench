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
typedef  int /*<<< orphan*/  u8 ;
struct qeth_card {int /*<<< orphan*/  conf_mutex; } ;
typedef  int ssize_t ;
typedef  enum qeth_prot_versions { ____Placeholder_qeth_prot_versions } qeth_prot_versions ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_IP_TYPE_VIPA ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int qeth_l3_modify_rxip_vipa (struct qeth_card*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int qeth_l3_parse_vipae (char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t qeth_l3_dev_vipa_add_store(const char *buf, size_t count,
			struct qeth_card *card, enum qeth_prot_versions proto)
{
	u8 addr[16] = {0, };
	int rc;

	mutex_lock(&card->conf_mutex);
	rc = qeth_l3_parse_vipae(buf, proto, addr);
	if (!rc)
		rc = qeth_l3_modify_rxip_vipa(card, true, addr,
					      QETH_IP_TYPE_VIPA, proto);
	mutex_unlock(&card->conf_mutex);
	return rc ? rc : count;
}