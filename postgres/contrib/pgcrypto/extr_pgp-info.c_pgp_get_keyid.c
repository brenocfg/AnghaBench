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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  PullFilter ;
typedef  int /*<<< orphan*/  MBuf ;

/* Variables and functions */
#define  PGP_PKT_MARKER 141 
#define  PGP_PKT_PRIV_61 140 
#define  PGP_PKT_PUBENCRYPTED_SESSKEY 139 
#define  PGP_PKT_PUBLIC_KEY 138 
#define  PGP_PKT_PUBLIC_SUBKEY 137 
#define  PGP_PKT_SECRET_KEY 136 
#define  PGP_PKT_SECRET_SUBKEY 135 
#define  PGP_PKT_SIGNATURE 134 
#define  PGP_PKT_SYMENCRYPTED_DATA 133 
#define  PGP_PKT_SYMENCRYPTED_DATA_MDC 132 
#define  PGP_PKT_SYMENCRYPTED_SESSKEY 131 
#define  PGP_PKT_TRUST 130 
#define  PGP_PKT_USER_ATTR 129 
#define  PGP_PKT_USER_ID 128 
 int PXE_PGP_CORRUPT_DATA ; 
 int PXE_PGP_MULTIPLE_KEYS ; 
 int PXE_PGP_NO_USABLE_KEY ; 
 int /*<<< orphan*/  any_key ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int pgp_create_pkt_reader (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int pgp_parse_pkt_hdr (int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ ) ; 
 int pgp_skip_packet (int /*<<< orphan*/ *) ; 
 int print_key (int*,char*) ; 
 int pullf_create_mbuf_reader (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pullf_free (int /*<<< orphan*/ *) ; 
 int read_pubenc_keyid (int /*<<< orphan*/ *,int*) ; 
 int read_pubkey_keyid (int /*<<< orphan*/ *,int*) ; 

int
pgp_get_keyid(MBuf *pgp_data, char *dst)
{
	int			res;
	PullFilter *src;
	PullFilter *pkt = NULL;
	int			len;
	uint8		tag;
	int			got_pub_key = 0,
				got_symenc_key = 0,
				got_pubenc_key = 0;
	int			got_data = 0;
	uint8		keyid_buf[8];
	int			got_main_key = 0;


	res = pullf_create_mbuf_reader(&src, pgp_data);
	if (res < 0)
		return res;

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
			case PGP_PKT_SECRET_KEY:
			case PGP_PKT_PUBLIC_KEY:
				/* main key is for signing, so ignore it */
				if (!got_main_key)
				{
					got_main_key = 1;
					res = pgp_skip_packet(pkt);
				}
				else
					res = PXE_PGP_MULTIPLE_KEYS;
				break;
			case PGP_PKT_SECRET_SUBKEY:
			case PGP_PKT_PUBLIC_SUBKEY:
				res = read_pubkey_keyid(pkt, keyid_buf);
				if (res < 0)
					break;
				if (res > 0)
					got_pub_key++;
				break;
			case PGP_PKT_PUBENCRYPTED_SESSKEY:
				got_pubenc_key++;
				res = read_pubenc_keyid(pkt, keyid_buf);
				break;
			case PGP_PKT_SYMENCRYPTED_DATA:
			case PGP_PKT_SYMENCRYPTED_DATA_MDC:
				/* don't skip it, just stop */
				got_data = 1;
				break;
			case PGP_PKT_SYMENCRYPTED_SESSKEY:
				got_symenc_key++;
				/* fall through */
			case PGP_PKT_SIGNATURE:
			case PGP_PKT_MARKER:
			case PGP_PKT_TRUST:
			case PGP_PKT_USER_ID:
			case PGP_PKT_USER_ATTR:
			case PGP_PKT_PRIV_61:
				res = pgp_skip_packet(pkt);
				break;
			default:
				res = PXE_PGP_CORRUPT_DATA;
		}

		if (pkt)
			pullf_free(pkt);
		pkt = NULL;

		if (res < 0 || got_data)
			break;
	}

	pullf_free(src);
	if (pkt)
		pullf_free(pkt);

	if (res < 0)
		return res;

	/* now check sanity */
	if (got_pub_key && got_pubenc_key)
		res = PXE_PGP_CORRUPT_DATA;

	if (got_pub_key > 1)
		res = PXE_PGP_MULTIPLE_KEYS;

	if (got_pubenc_key > 1)
		res = PXE_PGP_MULTIPLE_KEYS;

	/*
	 * if still ok, look what we got
	 */
	if (res >= 0)
	{
		if (got_pubenc_key || got_pub_key)
		{
			if (memcmp(keyid_buf, any_key, 8) == 0)
			{
				memcpy(dst, "ANYKEY", 7);
				res = 6;
			}
			else
				res = print_key(keyid_buf, dst);
		}
		else if (got_symenc_key)
		{
			memcpy(dst, "SYMKEY", 7);
			res = 6;
		}
		else
			res = PXE_PGP_NO_USABLE_KEY;
	}

	return res;
}