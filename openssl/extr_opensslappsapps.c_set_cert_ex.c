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
struct TYPE_3__ {char* member_0; int member_2; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ NAME_EX_TBL ;

/* Variables and functions */
#define  X509V3_EXT_DEFAULT 146 
#define  X509V3_EXT_DUMP_UNKNOWN 145 
#define  X509V3_EXT_ERROR_UNKNOWN 144 
#define  X509V3_EXT_PARSE_UNKNOWN 143 
#define  X509V3_EXT_UNKNOWN_MASK 142 
#define  X509_FLAG_CA 141 
#define  X509_FLAG_COMPAT 140 
#define  X509_FLAG_NO_ATTRIBUTES 139 
#define  X509_FLAG_NO_AUX 138 
#define  X509_FLAG_NO_EXTENSIONS 137 
#define  X509_FLAG_NO_HEADER 136 
#define  X509_FLAG_NO_ISSUER 135 
#define  X509_FLAG_NO_PUBKEY 134 
#define  X509_FLAG_NO_SERIAL 133 
#define  X509_FLAG_NO_SIGDUMP 132 
#define  X509_FLAG_NO_SIGNAME 131 
#define  X509_FLAG_NO_SUBJECT 130 
#define  X509_FLAG_NO_VALIDITY 129 
#define  X509_FLAG_NO_VERSION 128 
 int set_multi_opts (unsigned long*,char const*,TYPE_1__ const*) ; 

int set_cert_ex(unsigned long *flags, const char *arg)
{
    static const NAME_EX_TBL cert_tbl[] = {
        {"compatible", X509_FLAG_COMPAT, 0xffffffffl},
        {"ca_default", X509_FLAG_CA, 0xffffffffl},
        {"no_header", X509_FLAG_NO_HEADER, 0},
        {"no_version", X509_FLAG_NO_VERSION, 0},
        {"no_serial", X509_FLAG_NO_SERIAL, 0},
        {"no_signame", X509_FLAG_NO_SIGNAME, 0},
        {"no_validity", X509_FLAG_NO_VALIDITY, 0},
        {"no_subject", X509_FLAG_NO_SUBJECT, 0},
        {"no_issuer", X509_FLAG_NO_ISSUER, 0},
        {"no_pubkey", X509_FLAG_NO_PUBKEY, 0},
        {"no_extensions", X509_FLAG_NO_EXTENSIONS, 0},
        {"no_sigdump", X509_FLAG_NO_SIGDUMP, 0},
        {"no_aux", X509_FLAG_NO_AUX, 0},
        {"no_attributes", X509_FLAG_NO_ATTRIBUTES, 0},
        {"ext_default", X509V3_EXT_DEFAULT, X509V3_EXT_UNKNOWN_MASK},
        {"ext_error", X509V3_EXT_ERROR_UNKNOWN, X509V3_EXT_UNKNOWN_MASK},
        {"ext_parse", X509V3_EXT_PARSE_UNKNOWN, X509V3_EXT_UNKNOWN_MASK},
        {"ext_dump", X509V3_EXT_DUMP_UNKNOWN, X509V3_EXT_UNKNOWN_MASK},
        {NULL, 0, 0}
    };
    return set_multi_opts(flags, arg, cert_tbl);
}