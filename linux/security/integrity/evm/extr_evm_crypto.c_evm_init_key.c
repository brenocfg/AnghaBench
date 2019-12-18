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
struct TYPE_2__ {struct encrypted_key_payload** data; } ;
struct key {int /*<<< orphan*/  sem; TYPE_1__ payload; } ;
struct encrypted_key_payload {int /*<<< orphan*/  decrypted_datalen; int /*<<< orphan*/  decrypted_data; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  EVMKEY ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int evm_set_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  key_type_encrypted ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct key* request_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int evm_init_key(void)
{
	struct key *evm_key;
	struct encrypted_key_payload *ekp;
	int rc;

	evm_key = request_key(&key_type_encrypted, EVMKEY, NULL);
	if (IS_ERR(evm_key))
		return -ENOENT;

	down_read(&evm_key->sem);
	ekp = evm_key->payload.data[0];

	rc = evm_set_key(ekp->decrypted_data, ekp->decrypted_datalen);

	/* burn the original key contents */
	memset(ekp->decrypted_data, 0, ekp->decrypted_datalen);
	up_read(&evm_key->sem);
	key_put(evm_key);
	return rc;
}