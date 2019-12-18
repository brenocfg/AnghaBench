#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * from; } ;
typedef  TYPE_1__ substring_t ;
struct trusted_key_payload {int /*<<< orphan*/  migratable; } ;
struct trusted_key_options {int hash; int pcrinfo_len; unsigned long keyhandle; unsigned long pcrlock; unsigned int policydigest_len; unsigned long policyhandle; int /*<<< orphan*/  policydigest; int /*<<< orphan*/  blobauth; int /*<<< orphan*/  keyauth; int /*<<< orphan*/  keytype; int /*<<< orphan*/  pcrinfo; } ;

/* Variables and functions */
 int EINVAL ; 
 int HASH_ALGO_SHA1 ; 
 int HASH_ALGO_SHA256 ; 
 int HASH_ALGO__LAST ; 
 int MAX_OPT_ARGS ; 
 int MAX_PCRINFO_SIZE ; 
#define  Opt_blobauth 136 
#define  Opt_hash 135 
#define  Opt_keyauth 134 
#define  Opt_keyhandle 133 
#define  Opt_migratable 132 
#define  Opt_pcrinfo 131 
#define  Opt_pcrlock 130 
#define  Opt_policydigest 129 
#define  Opt_policyhandle 128 
 int /*<<< orphan*/  SEAL_keytype ; 
 int SHA1_DIGEST_SIZE ; 
 int /*<<< orphan*/  chip ; 
 int /*<<< orphan*/ * hash_algo_name ; 
 unsigned int* hash_digest_size ; 
 int hex2bin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  key_tokens ; 
 int kstrtoul (int /*<<< orphan*/ *,int,unsigned long*) ; 
 int match_token (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ *) ; 
 char* strsep (char**,char*) ; 
 scalar_t__ test_and_set_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  test_bit (int,unsigned long*) ; 
 int tpm_is_tpm2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int getoptions(char *c, struct trusted_key_payload *pay,
		      struct trusted_key_options *opt)
{
	substring_t args[MAX_OPT_ARGS];
	char *p = c;
	int token;
	int res;
	unsigned long handle;
	unsigned long lock;
	unsigned long token_mask = 0;
	unsigned int digest_len;
	int i;
	int tpm2;

	tpm2 = tpm_is_tpm2(chip);
	if (tpm2 < 0)
		return tpm2;

	opt->hash = tpm2 ? HASH_ALGO_SHA256 : HASH_ALGO_SHA1;

	while ((p = strsep(&c, " \t"))) {
		if (*p == '\0' || *p == ' ' || *p == '\t')
			continue;
		token = match_token(p, key_tokens, args);
		if (test_and_set_bit(token, &token_mask))
			return -EINVAL;

		switch (token) {
		case Opt_pcrinfo:
			opt->pcrinfo_len = strlen(args[0].from) / 2;
			if (opt->pcrinfo_len > MAX_PCRINFO_SIZE)
				return -EINVAL;
			res = hex2bin(opt->pcrinfo, args[0].from,
				      opt->pcrinfo_len);
			if (res < 0)
				return -EINVAL;
			break;
		case Opt_keyhandle:
			res = kstrtoul(args[0].from, 16, &handle);
			if (res < 0)
				return -EINVAL;
			opt->keytype = SEAL_keytype;
			opt->keyhandle = handle;
			break;
		case Opt_keyauth:
			if (strlen(args[0].from) != 2 * SHA1_DIGEST_SIZE)
				return -EINVAL;
			res = hex2bin(opt->keyauth, args[0].from,
				      SHA1_DIGEST_SIZE);
			if (res < 0)
				return -EINVAL;
			break;
		case Opt_blobauth:
			if (strlen(args[0].from) != 2 * SHA1_DIGEST_SIZE)
				return -EINVAL;
			res = hex2bin(opt->blobauth, args[0].from,
				      SHA1_DIGEST_SIZE);
			if (res < 0)
				return -EINVAL;
			break;
		case Opt_migratable:
			if (*args[0].from == '0')
				pay->migratable = 0;
			else
				return -EINVAL;
			break;
		case Opt_pcrlock:
			res = kstrtoul(args[0].from, 10, &lock);
			if (res < 0)
				return -EINVAL;
			opt->pcrlock = lock;
			break;
		case Opt_hash:
			if (test_bit(Opt_policydigest, &token_mask))
				return -EINVAL;
			for (i = 0; i < HASH_ALGO__LAST; i++) {
				if (!strcmp(args[0].from, hash_algo_name[i])) {
					opt->hash = i;
					break;
				}
			}
			if (i == HASH_ALGO__LAST)
				return -EINVAL;
			if  (!tpm2 && i != HASH_ALGO_SHA1) {
				pr_info("trusted_key: TPM 1.x only supports SHA-1.\n");
				return -EINVAL;
			}
			break;
		case Opt_policydigest:
			digest_len = hash_digest_size[opt->hash];
			if (!tpm2 || strlen(args[0].from) != (2 * digest_len))
				return -EINVAL;
			res = hex2bin(opt->policydigest, args[0].from,
				      digest_len);
			if (res < 0)
				return -EINVAL;
			opt->policydigest_len = digest_len;
			break;
		case Opt_policyhandle:
			if (!tpm2)
				return -EINVAL;
			res = kstrtoul(args[0].from, 16, &handle);
			if (res < 0)
				return -EINVAL;
			opt->policyhandle = handle;
			break;
		default:
			return -EINVAL;
		}
	}
	return 0;
}