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
typedef  int /*<<< orphan*/  TS_RESP_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  CONF ;

/* Variables and functions */
 int /*<<< orphan*/  ENV_SIGNER_KEY ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 char* NCONF_get_string (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * TS_CONF_load_key (char const*,char const*) ; 
 int /*<<< orphan*/  TS_RESP_CTX_set_signer_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_CONF_lookup_fail (char const*,int /*<<< orphan*/ ) ; 

int TS_CONF_set_signer_key(CONF *conf, const char *section,
                           const char *key, const char *pass,
                           TS_RESP_CTX *ctx)
{
    int ret = 0;
    EVP_PKEY *key_obj = NULL;
    if (!key)
        key = NCONF_get_string(conf, section, ENV_SIGNER_KEY);
    if (!key) {
        ts_CONF_lookup_fail(section, ENV_SIGNER_KEY);
        goto err;
    }
    if ((key_obj = TS_CONF_load_key(key, pass)) == NULL)
        goto err;
    if (!TS_RESP_CTX_set_signer_key(ctx, key_obj))
        goto err;

    ret = 1;
 err:
    EVP_PKEY_free(key_obj);
    return ret;
}