#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* exptext; TYPE_4__* noticeref; } ;
typedef  TYPE_3__ USERNOTICE ;
struct TYPE_9__ {int /*<<< orphan*/  noticenos; TYPE_1__* organization; } ;
struct TYPE_7__ {char* data; } ;
struct TYPE_6__ {char* data; } ;
typedef  TYPE_4__ NOTICEREF ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,int,char*,char*) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* i2s_ASN1_INTEGER (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sk_ASN1_INTEGER_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sk_ASN1_INTEGER_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void print_notice(BIO *out, USERNOTICE *notice, int indent)
{
    int i;
    if (notice->noticeref) {
        NOTICEREF *ref;
        ref = notice->noticeref;
        BIO_printf(out, "%*sOrganization: %s\n", indent, "",
                   ref->organization->data);
        BIO_printf(out, "%*sNumber%s: ", indent, "",
                   sk_ASN1_INTEGER_num(ref->noticenos) > 1 ? "s" : "");
        for (i = 0; i < sk_ASN1_INTEGER_num(ref->noticenos); i++) {
            ASN1_INTEGER *num;
            char *tmp;
            num = sk_ASN1_INTEGER_value(ref->noticenos, i);
            if (i)
                BIO_puts(out, ", ");
            if (num == NULL)
                BIO_puts(out, "(null)");
            else {
                tmp = i2s_ASN1_INTEGER(NULL, num);
                if (tmp == NULL)
                    return;
                BIO_puts(out, tmp);
                OPENSSL_free(tmp);
            }
        }
        if (notice->exptext)
            BIO_puts(out, "\n");
    }
    if (notice->exptext)
        BIO_printf(out, "%*sExplicit Text: %s", indent, "",
                   notice->exptext->data);
}