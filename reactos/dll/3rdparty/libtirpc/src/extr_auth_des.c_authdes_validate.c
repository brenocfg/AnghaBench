#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct timeval {int dummy; } ;
struct opaque_auth {int oa_length; scalar_t__ oa_base; } ;
struct TYPE_9__ {void* tv_usec; void* tv_sec; } ;
struct authdes_verf {int /*<<< orphan*/  adv_nickname; TYPE_2__ adv_timestamp; void* adv_int_u; } ;
struct TYPE_10__ {int /*<<< orphan*/  adc_namekind; } ;
struct ad_private {TYPE_3__ ad_cred; int /*<<< orphan*/  ad_nickname; int /*<<< orphan*/  ad_timestamp; } ;
struct TYPE_8__ {void* low; void* high; } ;
struct TYPE_11__ {scalar_t__ c; TYPE_1__ key; } ;
typedef  TYPE_4__ des_block ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_12__ {int /*<<< orphan*/  ah_key; } ;
typedef  TYPE_5__ AUTH ;

/* Variables and functions */
 int /*<<< orphan*/  ADN_NICKNAME ; 
 struct ad_private* AUTH_PRIVATE (TYPE_5__*) ; 
 int BYTES_PER_XDR_UNIT ; 
 int DES_DECRYPT ; 
 scalar_t__ DES_FAILED (int) ; 
 int DES_HW ; 
 int /*<<< orphan*/  FALSE ; 
 void* IXDR_GET_INT32 (void**) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bcmp (char*,char*,int) ; 
 int ecb_crypt (char*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool_t
authdes_validate(AUTH *auth, struct opaque_auth *rverf)
{
/* LINTED pointer alignment */
	struct ad_private *ad = AUTH_PRIVATE(auth);
	struct authdes_verf verf;
	int status;
	uint32_t *ixdr;
	des_block buf;

	if (rverf->oa_length != (2 + 1) * BYTES_PER_XDR_UNIT) {
		return (FALSE);
	}
/* LINTED pointer alignment */
	ixdr = (uint32_t *)rverf->oa_base;
	buf.key.high = (uint32_t)*ixdr++;
	buf.key.low = (uint32_t)*ixdr++;
	verf.adv_int_u = (uint32_t)*ixdr++;

	/*
	 * Decrypt the timestamp
	 */
	status = ecb_crypt((char *)&auth->ah_key, (char *)&buf,
		(u_int)sizeof (des_block), DES_DECRYPT | DES_HW);

	if (DES_FAILED(status)) {
		//syslog(LOG_ERR, "authdes_validate: DES decryption failure");
		return (FALSE);
	}

	/*
	 * xdr the decrypted timestamp
	 */
/* LINTED pointer alignment */
	ixdr = (uint32_t *)buf.c;
	verf.adv_timestamp.tv_sec = IXDR_GET_INT32(ixdr) + 1;
	verf.adv_timestamp.tv_usec = IXDR_GET_INT32(ixdr);

	/*
	 * validate
	 */
	if (bcmp((char *)&ad->ad_timestamp, (char *)&verf.adv_timestamp,
		 sizeof(struct timeval)) != 0) {
		//syslog(LOG_DEBUG, "authdes_validate: verifier mismatch");
		return (FALSE);
	}

	/*
	 * We have a nickname now, let's use it
	 */
	ad->ad_nickname = verf.adv_nickname;
	ad->ad_cred.adc_namekind = ADN_NICKNAME;
	return (TRUE);
}