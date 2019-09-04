#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; } ;
struct xfrm_state {TYPE_5__* ealg; TYPE_4__* aalg; struct crypto_aead* data; scalar_t__ geniv; TYPE_1__ props; } ;
struct TYPE_7__ {int icv_fullbits; } ;
struct TYPE_8__ {TYPE_2__ auth; } ;
struct xfrm_algo_desc {TYPE_3__ uinfo; } ;
struct rtattr {int /*<<< orphan*/  rta_len; int /*<<< orphan*/  rta_type; } ;
struct crypto_authenc_key_param {int /*<<< orphan*/  enckeylen; } ;
struct crypto_aead {int dummy; } ;
struct TYPE_10__ {char* alg_name; int alg_key_len; int /*<<< orphan*/  alg_key; } ;
struct TYPE_9__ {char* alg_name; int alg_key_len; int alg_trunc_len; int /*<<< orphan*/  alg_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CRYPTO_AUTHENC_KEYA_PARAM ; 
 int CRYPTO_MAX_ALG_NAME ; 
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct crypto_aead*) ; 
 int PTR_ERR (struct crypto_aead*) ; 
 struct crypto_authenc_key_param* RTA_DATA (struct rtattr*) ; 
 int /*<<< orphan*/  RTA_LENGTH (int) ; 
 int RTA_SPACE (int) ; 
 int XFRM_STATE_ESN ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int crypto_aead_authsize (struct crypto_aead*) ; 
 int crypto_aead_setauthsize (struct crypto_aead*,int) ; 
 int crypto_aead_setkey (struct crypto_aead*,char*,unsigned int) ; 
 struct crypto_aead* crypto_alloc_aead (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,char*,int,int) ; 
 int snprintf (char*,int,char*,char*,char*,char*,char*,char*) ; 
 struct xfrm_algo_desc* xfrm_aalg_get_byname (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esp_init_authenc(struct xfrm_state *x)
{
	struct crypto_aead *aead;
	struct crypto_authenc_key_param *param;
	struct rtattr *rta;
	char *key;
	char *p;
	char authenc_name[CRYPTO_MAX_ALG_NAME];
	unsigned int keylen;
	int err;

	err = -EINVAL;
	if (!x->ealg)
		goto error;

	err = -ENAMETOOLONG;

	if ((x->props.flags & XFRM_STATE_ESN)) {
		if (snprintf(authenc_name, CRYPTO_MAX_ALG_NAME,
			     "%s%sauthencesn(%s,%s)%s",
			     x->geniv ?: "", x->geniv ? "(" : "",
			     x->aalg ? x->aalg->alg_name : "digest_null",
			     x->ealg->alg_name,
			     x->geniv ? ")" : "") >= CRYPTO_MAX_ALG_NAME)
			goto error;
	} else {
		if (snprintf(authenc_name, CRYPTO_MAX_ALG_NAME,
			     "%s%sauthenc(%s,%s)%s",
			     x->geniv ?: "", x->geniv ? "(" : "",
			     x->aalg ? x->aalg->alg_name : "digest_null",
			     x->ealg->alg_name,
			     x->geniv ? ")" : "") >= CRYPTO_MAX_ALG_NAME)
			goto error;
	}

	aead = crypto_alloc_aead(authenc_name, 0, 0);
	err = PTR_ERR(aead);
	if (IS_ERR(aead))
		goto error;

	x->data = aead;

	keylen = (x->aalg ? (x->aalg->alg_key_len + 7) / 8 : 0) +
		 (x->ealg->alg_key_len + 7) / 8 + RTA_SPACE(sizeof(*param));
	err = -ENOMEM;
	key = kmalloc(keylen, GFP_KERNEL);
	if (!key)
		goto error;

	p = key;
	rta = (void *)p;
	rta->rta_type = CRYPTO_AUTHENC_KEYA_PARAM;
	rta->rta_len = RTA_LENGTH(sizeof(*param));
	param = RTA_DATA(rta);
	p += RTA_SPACE(sizeof(*param));

	if (x->aalg) {
		struct xfrm_algo_desc *aalg_desc;

		memcpy(p, x->aalg->alg_key, (x->aalg->alg_key_len + 7) / 8);
		p += (x->aalg->alg_key_len + 7) / 8;

		aalg_desc = xfrm_aalg_get_byname(x->aalg->alg_name, 0);
		BUG_ON(!aalg_desc);

		err = -EINVAL;
		if (aalg_desc->uinfo.auth.icv_fullbits / 8 !=
		    crypto_aead_authsize(aead)) {
			pr_info("ESP: %s digestsize %u != %hu\n",
				x->aalg->alg_name,
				crypto_aead_authsize(aead),
				aalg_desc->uinfo.auth.icv_fullbits / 8);
			goto free_key;
		}

		err = crypto_aead_setauthsize(
			aead, x->aalg->alg_trunc_len / 8);
		if (err)
			goto free_key;
	}

	param->enckeylen = cpu_to_be32((x->ealg->alg_key_len + 7) / 8);
	memcpy(p, x->ealg->alg_key, (x->ealg->alg_key_len + 7) / 8);

	err = crypto_aead_setkey(aead, key, keylen);

free_key:
	kfree(key);

error:
	return err;
}