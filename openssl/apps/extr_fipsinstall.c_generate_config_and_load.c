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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int /*<<< orphan*/  CONF_modules_load (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NCONF_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * app_load_config_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_config_fips_section (int /*<<< orphan*/ *,char const*,unsigned char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_config_header (int /*<<< orphan*/ *,char const*,char const*) ; 

__attribute__((used)) static CONF *generate_config_and_load(const char *prov_name,
                                      const char *section,
                                      unsigned char *module_mac,
                                      size_t module_mac_len)
{
    BIO *mem_bio = NULL;
    CONF *conf = NULL;

    mem_bio = BIO_new(BIO_s_mem());
    if (mem_bio  == NULL)
        return 0;
    if (!write_config_header(mem_bio, prov_name, section)
         || !write_config_fips_section(mem_bio, section, module_mac,
                                       module_mac_len, NULL, 0))
        goto end;

    conf = app_load_config_bio(mem_bio, NULL);
    if (conf == NULL)
        goto end;

    if (!CONF_modules_load(conf, NULL, 0))
        goto end;
    BIO_free(mem_bio);
    return conf;
end:
    NCONF_free(conf);
    BIO_free(mem_bio);
    return NULL;
}