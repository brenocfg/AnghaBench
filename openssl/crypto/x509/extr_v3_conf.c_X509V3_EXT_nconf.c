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
typedef  int /*<<< orphan*/  X509_EXTENSION ;
typedef  int /*<<< orphan*/  X509V3_CTX ;
typedef  int /*<<< orphan*/  CONF ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_add_error_data (int,char*,char const*,char*,char const*) ; 
 int /*<<< orphan*/  OBJ_sn2nid (char const*) ; 
 int /*<<< orphan*/  X509V3_F_X509V3_EXT_NCONF ; 
 int /*<<< orphan*/  X509V3_R_ERROR_IN_EXTENSION ; 
 int /*<<< orphan*/  X509V3err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * do_ext_nconf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char const*) ; 
 int v3_check_critical (char const**) ; 
 int v3_check_generic (char const**) ; 
 int /*<<< orphan*/ * v3_generic_extension (char const*,char const*,int,int,int /*<<< orphan*/ *) ; 

X509_EXTENSION *X509V3_EXT_nconf(CONF *conf, X509V3_CTX *ctx, const char *name,
                                 const char *value)
{
    int crit;
    int ext_type;
    X509_EXTENSION *ret;
    crit = v3_check_critical(&value);
    if ((ext_type = v3_check_generic(&value)))
        return v3_generic_extension(name, value, crit, ext_type, ctx);
    ret = do_ext_nconf(conf, ctx, OBJ_sn2nid(name), crit, value);
    if (!ret) {
        X509V3err(X509V3_F_X509V3_EXT_NCONF, X509V3_R_ERROR_IN_EXTENSION);
        ERR_add_error_data(4, "name=", name, ", value=", value);
    }
    return ret;
}