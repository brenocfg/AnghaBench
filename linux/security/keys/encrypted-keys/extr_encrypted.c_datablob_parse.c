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
typedef  int /*<<< orphan*/  substring_t ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_OPT_ARGS ; 
#define  Opt_default 135 
#define  Opt_ecryptfs 134 
#define  Opt_enc32 133 
#define  Opt_err 132 
#define  Opt_error 131 
#define  Opt_load 130 
#define  Opt_new 129 
#define  Opt_update 128 
 int /*<<< orphan*/  key_format_tokens ; 
 int /*<<< orphan*/  key_tokens ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 char* strsep (char**,char*) ; 
 scalar_t__ valid_master_desc (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int datablob_parse(char *datablob, const char **format,
			  char **master_desc, char **decrypted_datalen,
			  char **hex_encoded_iv)
{
	substring_t args[MAX_OPT_ARGS];
	int ret = -EINVAL;
	int key_cmd;
	int key_format;
	char *p, *keyword;

	keyword = strsep(&datablob, " \t");
	if (!keyword) {
		pr_info("encrypted_key: insufficient parameters specified\n");
		return ret;
	}
	key_cmd = match_token(keyword, key_tokens, args);

	/* Get optional format: default | ecryptfs */
	p = strsep(&datablob, " \t");
	if (!p) {
		pr_err("encrypted_key: insufficient parameters specified\n");
		return ret;
	}

	key_format = match_token(p, key_format_tokens, args);
	switch (key_format) {
	case Opt_ecryptfs:
	case Opt_enc32:
	case Opt_default:
		*format = p;
		*master_desc = strsep(&datablob, " \t");
		break;
	case Opt_error:
		*master_desc = p;
		break;
	}

	if (!*master_desc) {
		pr_info("encrypted_key: master key parameter is missing\n");
		goto out;
	}

	if (valid_master_desc(*master_desc, NULL) < 0) {
		pr_info("encrypted_key: master key parameter \'%s\' "
			"is invalid\n", *master_desc);
		goto out;
	}

	if (decrypted_datalen) {
		*decrypted_datalen = strsep(&datablob, " \t");
		if (!*decrypted_datalen) {
			pr_info("encrypted_key: keylen parameter is missing\n");
			goto out;
		}
	}

	switch (key_cmd) {
	case Opt_new:
		if (!decrypted_datalen) {
			pr_info("encrypted_key: keyword \'%s\' not allowed "
				"when called from .update method\n", keyword);
			break;
		}
		ret = 0;
		break;
	case Opt_load:
		if (!decrypted_datalen) {
			pr_info("encrypted_key: keyword \'%s\' not allowed "
				"when called from .update method\n", keyword);
			break;
		}
		*hex_encoded_iv = strsep(&datablob, " \t");
		if (!*hex_encoded_iv) {
			pr_info("encrypted_key: hex blob is missing\n");
			break;
		}
		ret = 0;
		break;
	case Opt_update:
		if (decrypted_datalen) {
			pr_info("encrypted_key: keyword \'%s\' not allowed "
				"when called from .instantiate method\n",
				keyword);
			break;
		}
		ret = 0;
		break;
	case Opt_err:
		pr_info("encrypted_key: keyword \'%s\' not recognized\n",
			keyword);
		break;
	}
out:
	return ret;
}