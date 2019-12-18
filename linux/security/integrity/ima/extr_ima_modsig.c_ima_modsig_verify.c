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
struct modsig {int /*<<< orphan*/  pkcs7_msg; } ;
struct key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFYING_MODULE_SIGNATURE ; 
 int verify_pkcs7_message_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct key*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ima_modsig_verify(struct key *keyring, const struct modsig *modsig)
{
	return verify_pkcs7_message_sig(NULL, 0, modsig->pkcs7_msg, keyring,
					VERIFYING_MODULE_SIGNATURE, NULL, NULL);
}