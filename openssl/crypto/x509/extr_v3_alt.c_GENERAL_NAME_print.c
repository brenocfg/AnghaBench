#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  rid; TYPE_6__* ip; int /*<<< orphan*/  dirn; int /*<<< orphan*/  ia5; TYPE_5__* otherName; } ;
struct TYPE_17__ {int type; TYPE_7__ d; } ;
struct TYPE_15__ {unsigned char* data; int length; } ;
struct TYPE_14__ {TYPE_4__* value; int /*<<< orphan*/  type_id; } ;
struct TYPE_12__ {TYPE_2__* utf8string; TYPE_1__* ia5string; } ;
struct TYPE_13__ {TYPE_3__ value; int /*<<< orphan*/  type; } ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_8__ GENERAL_NAME ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
#define  GEN_DIRNAME 140 
#define  GEN_DNS 139 
#define  GEN_EDIPARTY 138 
#define  GEN_EMAIL 137 
#define  GEN_IPADD 136 
#define  GEN_OTHERNAME 135 
#define  GEN_RID 134 
#define  GEN_URI 133 
#define  GEN_X400 132 
#define  NID_SRVName 131 
#define  NID_XmppAddr 130 
#define  NID_id_on_SmtpUTF8Mailbox 129 
#define  NID_ms_upn 128 
 int OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_ASN1_IA5STRING ; 
 int /*<<< orphan*/  V_ASN1_UTF8STRING ; 
 int /*<<< orphan*/  X509_NAME_print_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XN_FLAG_ONELINE ; 
 int /*<<< orphan*/  i2a_ASN1_OBJECT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int GENERAL_NAME_print(BIO *out, GENERAL_NAME *gen)
{
    unsigned char *p;
    int i, nid;

    switch (gen->type) {
    case GEN_OTHERNAME:
        nid = OBJ_obj2nid(gen->d.otherName->type_id);
        /* Validate the types are as we expect before we use them */
        if ((nid == NID_SRVName
             && gen->d.otherName->value->type != V_ASN1_IA5STRING)
                || (nid != NID_SRVName
                    && gen->d.otherName->value->type != V_ASN1_UTF8STRING)) {
            BIO_printf(out, "othername:<unsupported>");
            break;
        }

        switch (nid) {
        case NID_id_on_SmtpUTF8Mailbox:
            BIO_printf(out, "othername:SmtpUTF8Mailbox:%s",
                       gen->d.otherName->value->value.utf8string->data);
            break;
        case NID_XmppAddr:
            BIO_printf(out, "othername:XmppAddr:%s",
                       gen->d.otherName->value->value.utf8string->data);
            break;
        case NID_SRVName:
            BIO_printf(out, "othername:SRVName:%s",
                       gen->d.otherName->value->value.ia5string->data);
            break;
        case NID_ms_upn:
            BIO_printf(out, "othername:UPN:%s",
                       gen->d.otherName->value->value.utf8string->data);
            break;
        default:
            BIO_printf(out, "othername:<unsupported>");
            break;
        }
        break;

    case GEN_X400:
        BIO_printf(out, "X400Name:<unsupported>");
        break;

    case GEN_EDIPARTY:
        /* Maybe fix this: it is supported now */
        BIO_printf(out, "EdiPartyName:<unsupported>");
        break;

    case GEN_EMAIL:
        BIO_printf(out, "email:");
        ASN1_STRING_print(out, gen->d.ia5);
        break;

    case GEN_DNS:
        BIO_printf(out, "DNS:");
        ASN1_STRING_print(out, gen->d.ia5);
        break;

    case GEN_URI:
        BIO_printf(out, "URI:");
        ASN1_STRING_print(out, gen->d.ia5);
        break;

    case GEN_DIRNAME:
        BIO_printf(out, "DirName:");
        X509_NAME_print_ex(out, gen->d.dirn, 0, XN_FLAG_ONELINE);
        break;

    case GEN_IPADD:
        p = gen->d.ip->data;
        if (gen->d.ip->length == 4)
            BIO_printf(out, "IP Address:%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
        else if (gen->d.ip->length == 16) {
            BIO_printf(out, "IP Address");
            for (i = 0; i < 8; i++) {
                BIO_printf(out, ":%X", p[0] << 8 | p[1]);
                p += 2;
            }
        } else {
            BIO_printf(out, "IP Address:<invalid>");
            break;
        }
        break;

    case GEN_RID:
        BIO_printf(out, "Registered ID:");
        i2a_ASN1_OBJECT(out, gen->d.rid);
        break;
    }
    return 1;
}