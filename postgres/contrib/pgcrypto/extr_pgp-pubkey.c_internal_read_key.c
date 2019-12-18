#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
struct TYPE_6__ {scalar_t__ can_encrypt; } ;
typedef  int /*<<< orphan*/  PullFilter ;
typedef  TYPE_1__ PGP_PubKey ;

/* Variables and functions */
#define  PGP_PKT_MARKER 137 
#define  PGP_PKT_PRIV_61 136 
#define  PGP_PKT_PUBLIC_KEY 135 
#define  PGP_PKT_PUBLIC_SUBKEY 134 
#define  PGP_PKT_SECRET_KEY 133 
#define  PGP_PKT_SECRET_SUBKEY 132 
#define  PGP_PKT_SIGNATURE 131 
#define  PGP_PKT_TRUST 130 
#define  PGP_PKT_USER_ATTR 129 
#define  PGP_PKT_USER_ID 128 
 int PXE_PGP_EXPECT_PUBLIC_KEY ; 
 int PXE_PGP_EXPECT_SECRET_KEY ; 
 int PXE_PGP_MULTIPLE_KEYS ; 
 int PXE_PGP_MULTIPLE_SUBKEYS ; 
 int PXE_PGP_NO_USABLE_KEY ; 
 int PXE_PGP_UNEXPECTED_PKT ; 
 int _pgp_read_public_key (int /*<<< orphan*/ *,TYPE_1__**) ; 
 int pgp_create_pkt_reader (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgp_key_free (TYPE_1__*) ; 
 int pgp_parse_pkt_hdr (int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ ) ; 
 int pgp_skip_packet (int /*<<< orphan*/ *) ; 
 int process_secret_key (int /*<<< orphan*/ *,TYPE_1__**,int const*,int) ; 
 int /*<<< orphan*/  pullf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_debug (char*,int) ; 

__attribute__((used)) static int
internal_read_key(PullFilter *src, PGP_PubKey **pk_p,
				  const uint8 *psw, int psw_len, int pubtype)
{
	PullFilter *pkt = NULL;
	int			res;
	uint8		tag;
	int			len;
	PGP_PubKey *enc_key = NULL;
	PGP_PubKey *pk = NULL;
	int			got_main_key = 0;

	/*
	 * Search for encryption key.
	 *
	 * Error out on anything fancy.
	 */
	while (1)
	{
		res = pgp_parse_pkt_hdr(src, &tag, &len, 0);
		if (res <= 0)
			break;
		res = pgp_create_pkt_reader(&pkt, src, len, res, NULL);
		if (res < 0)
			break;

		switch (tag)
		{
			case PGP_PKT_PUBLIC_KEY:
			case PGP_PKT_SECRET_KEY:
				if (got_main_key)
				{
					res = PXE_PGP_MULTIPLE_KEYS;
					break;
				}
				got_main_key = 1;
				res = pgp_skip_packet(pkt);
				break;

			case PGP_PKT_PUBLIC_SUBKEY:
				if (pubtype != 0)
					res = PXE_PGP_EXPECT_SECRET_KEY;
				else
					res = _pgp_read_public_key(pkt, &pk);
				break;

			case PGP_PKT_SECRET_SUBKEY:
				if (pubtype != 1)
					res = PXE_PGP_EXPECT_PUBLIC_KEY;
				else
					res = process_secret_key(pkt, &pk, psw, psw_len);
				break;

			case PGP_PKT_SIGNATURE:
			case PGP_PKT_MARKER:
			case PGP_PKT_TRUST:
			case PGP_PKT_USER_ID:
			case PGP_PKT_USER_ATTR:
			case PGP_PKT_PRIV_61:
				res = pgp_skip_packet(pkt);
				break;
			default:
				px_debug("unknown/unexpected packet: %d", tag);
				res = PXE_PGP_UNEXPECTED_PKT;
		}
		pullf_free(pkt);
		pkt = NULL;

		if (pk != NULL)
		{
			if (res >= 0 && pk->can_encrypt)
			{
				if (enc_key == NULL)
				{
					enc_key = pk;
					pk = NULL;
				}
				else
					res = PXE_PGP_MULTIPLE_SUBKEYS;
			}

			if (pk)
				pgp_key_free(pk);
			pk = NULL;
		}

		if (res < 0)
			break;
	}

	if (pkt)
		pullf_free(pkt);

	if (res < 0)
	{
		if (enc_key)
			pgp_key_free(enc_key);
		return res;
	}

	if (!enc_key)
		res = PXE_PGP_NO_USABLE_KEY;
	else
		*pk_p = enc_key;
	return res;
}