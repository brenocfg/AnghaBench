#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int sup_chars; int getset_timeout_sup; } ;
struct TYPE_4__ {TYPE_1__ vnicc; } ;
struct qeth_card {TYPE_2__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPA_VNICC_SET_TIMEOUT ; 
 int QETH_VNICC_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  qeth_l2_vnicc_getset_timeout (struct qeth_card*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool qeth_l2_vnicc_recover_timeout(struct qeth_card *card, u32 vnicc,
					  u32 *timeout)
{
	if (card->options.vnicc.sup_chars & vnicc &&
	    card->options.vnicc.getset_timeout_sup & vnicc &&
	    !qeth_l2_vnicc_getset_timeout(card, vnicc, IPA_VNICC_SET_TIMEOUT,
					  timeout))
		return false;
	*timeout = QETH_VNICC_DEFAULT_TIMEOUT;
	return true;
}