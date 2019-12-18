#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_4__ {int algo; int /*<<< orphan*/  key_id; } ;
typedef  int /*<<< orphan*/  PullFilter ;
typedef  TYPE_1__ PGP_PubKey ;

/* Variables and functions */
#define  PGP_PUB_ELG_ENCRYPT 130 
#define  PGP_PUB_RSA_ENCRYPT 129 
#define  PGP_PUB_RSA_ENCRYPT_SIGN 128 
 int _pgp_read_public_key (int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pgp_key_free (TYPE_1__*) ; 
 int pgp_skip_packet (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
read_pubkey_keyid(PullFilter *pkt, uint8 *keyid_buf)
{
	int			res;
	PGP_PubKey *pk = NULL;

	res = _pgp_read_public_key(pkt, &pk);
	if (res < 0)
		goto err;

	/* skip secret key part, if it exists */
	res = pgp_skip_packet(pkt);
	if (res < 0)
		goto err;

	/* is it encryption key */
	switch (pk->algo)
	{
		case PGP_PUB_ELG_ENCRYPT:
		case PGP_PUB_RSA_ENCRYPT:
		case PGP_PUB_RSA_ENCRYPT_SIGN:
			memcpy(keyid_buf, pk->key_id, 8);
			res = 1;
			break;
		default:
			res = 0;
	}

err:
	pgp_key_free(pk);
	return res;
}