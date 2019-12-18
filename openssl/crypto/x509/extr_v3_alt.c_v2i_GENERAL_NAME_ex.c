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
typedef  int /*<<< orphan*/  X509V3_EXT_METHOD ;
typedef  int /*<<< orphan*/  X509V3_CTX ;
struct TYPE_3__ {char* name; char* value; } ;
typedef  int /*<<< orphan*/  GENERAL_NAME ;
typedef  TYPE_1__ CONF_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_add_error_data (int,char*,char*) ; 
 int GEN_DIRNAME ; 
 int GEN_DNS ; 
 int GEN_EMAIL ; 
 int GEN_IPADD ; 
 int GEN_OTHERNAME ; 
 int GEN_RID ; 
 int GEN_URI ; 
 int /*<<< orphan*/  X509V3_F_V2I_GENERAL_NAME_EX ; 
 int /*<<< orphan*/  X509V3_R_MISSING_VALUE ; 
 int /*<<< orphan*/  X509V3_R_UNSUPPORTED_OPTION ; 
 int /*<<< orphan*/  X509V3err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * a2i_GENERAL_NAME (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  v3_name_cmp (char*,char*) ; 

GENERAL_NAME *v2i_GENERAL_NAME_ex(GENERAL_NAME *out,
                                  const X509V3_EXT_METHOD *method,
                                  X509V3_CTX *ctx, CONF_VALUE *cnf, int is_nc)
{
    int type;

    char *name, *value;

    name = cnf->name;
    value = cnf->value;

    if (!value) {
        X509V3err(X509V3_F_V2I_GENERAL_NAME_EX, X509V3_R_MISSING_VALUE);
        return NULL;
    }

    if (!v3_name_cmp(name, "email"))
        type = GEN_EMAIL;
    else if (!v3_name_cmp(name, "URI"))
        type = GEN_URI;
    else if (!v3_name_cmp(name, "DNS"))
        type = GEN_DNS;
    else if (!v3_name_cmp(name, "RID"))
        type = GEN_RID;
    else if (!v3_name_cmp(name, "IP"))
        type = GEN_IPADD;
    else if (!v3_name_cmp(name, "dirName"))
        type = GEN_DIRNAME;
    else if (!v3_name_cmp(name, "otherName"))
        type = GEN_OTHERNAME;
    else {
        X509V3err(X509V3_F_V2I_GENERAL_NAME_EX, X509V3_R_UNSUPPORTED_OPTION);
        ERR_add_error_data(2, "name=", name);
        return NULL;
    }

    return a2i_GENERAL_NAME(out, method, ctx, type, value, is_nc);

}