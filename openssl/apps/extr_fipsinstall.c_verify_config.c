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
typedef  int /*<<< orphan*/  CONF ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  INSTALL_STATUS_VAL ; 
 int /*<<< orphan*/  NCONF_free (int /*<<< orphan*/ *) ; 
 char* NCONF_get_string (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_hexstr2buf (char*,long*) ; 
 int /*<<< orphan*/  OSSL_PROV_FIPS_PARAM_INSTALL_MAC ; 
 int /*<<< orphan*/  OSSL_PROV_FIPS_PARAM_INSTALL_STATUS ; 
 int /*<<< orphan*/  OSSL_PROV_FIPS_PARAM_INSTALL_VERSION ; 
 int /*<<< orphan*/  OSSL_PROV_FIPS_PARAM_MODULE_MAC ; 
 int /*<<< orphan*/  VERSION_VAL ; 
 int /*<<< orphan*/ * app_load_config (char const*) ; 
 int /*<<< orphan*/  bio_err ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,size_t) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int verify_config(const char *infile, const char *section,
                         unsigned char *module_mac, size_t module_mac_len,
                         unsigned char *install_mac, size_t install_mac_len)
{
    int ret = 0;
    char *s = NULL;
    unsigned char *buf1 = NULL, *buf2 = NULL;
    long len;
    CONF *conf = NULL;

    /* read in the existing values and check they match the saved values */
    conf = app_load_config(infile);
    if (conf == NULL)
        goto end;

    s = NCONF_get_string(conf, section, OSSL_PROV_FIPS_PARAM_INSTALL_VERSION);
    if (s == NULL || strcmp(s, VERSION_VAL) != 0) {
        BIO_printf(bio_err, "version not found\n");
        goto end;
    }
    s = NCONF_get_string(conf, section, OSSL_PROV_FIPS_PARAM_INSTALL_STATUS);
    if (s == NULL || strcmp(s, INSTALL_STATUS_VAL) != 0) {
        BIO_printf(bio_err, "install status not found\n");
        goto end;
    }
    s = NCONF_get_string(conf, section, OSSL_PROV_FIPS_PARAM_MODULE_MAC);
    if (s == NULL) {
        BIO_printf(bio_err, "Module integrity MAC not found\n");
        goto end;
    }
    buf1 = OPENSSL_hexstr2buf(s, &len);
    if (buf1 == NULL
            || (size_t)len != module_mac_len
            || memcmp(module_mac, buf1, module_mac_len) != 0) {
        BIO_printf(bio_err, "Module integrity mismatch\n");
        goto end;
    }
    s = NCONF_get_string(conf, section, OSSL_PROV_FIPS_PARAM_INSTALL_MAC);
    if (s == NULL) {
        BIO_printf(bio_err, "Install indicator MAC not found\n");
        goto end;
    }
    buf2 = OPENSSL_hexstr2buf(s, &len);
    if (buf2 == NULL
            || (size_t)len != install_mac_len
            || memcmp(install_mac, buf2, install_mac_len) != 0) {
        BIO_printf(bio_err, "Install indicator status mismatch\n");
        goto end;
    }
    ret = 1;
end:
    OPENSSL_free(buf1);
    OPENSSL_free(buf2);
    NCONF_free(conf);
    return ret;
}