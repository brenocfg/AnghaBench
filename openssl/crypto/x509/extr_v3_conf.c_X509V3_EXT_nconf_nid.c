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
 int /*<<< orphan*/  OBJ_nid2sn (int) ; 
 int /*<<< orphan*/ * do_ext_nconf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,char const*) ; 
 int v3_check_critical (char const**) ; 
 int v3_check_generic (char const**) ; 
 int /*<<< orphan*/ * v3_generic_extension (int /*<<< orphan*/ ,char const*,int,int,int /*<<< orphan*/ *) ; 

X509_EXTENSION *X509V3_EXT_nconf_nid(CONF *conf, X509V3_CTX *ctx, int ext_nid,
                                     const char *value)
{
    int crit;
    int ext_type;
    crit = v3_check_critical(&value);
    if ((ext_type = v3_check_generic(&value)))
        return v3_generic_extension(OBJ_nid2sn(ext_nid),
                                    value, crit, ext_type, ctx);
    return do_ext_nconf(conf, ctx, ext_nid, crit, value);
}