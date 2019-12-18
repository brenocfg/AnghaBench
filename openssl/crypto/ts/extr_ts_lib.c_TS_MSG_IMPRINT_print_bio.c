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
struct TYPE_3__ {int /*<<< orphan*/ * hashed_msg; int /*<<< orphan*/  hash_algo; } ;
typedef  TYPE_1__ TS_MSG_IMPRINT ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 scalar_t__ ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_STRING_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_dump_indent (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  TS_X509_ALGOR_print_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int TS_MSG_IMPRINT_print_bio(BIO *bio, TS_MSG_IMPRINT *a)
{
    ASN1_OCTET_STRING *msg;

    TS_X509_ALGOR_print_bio(bio, a->hash_algo);

    BIO_printf(bio, "Message data:\n");
    msg = a->hashed_msg;
    BIO_dump_indent(bio, (const char *)ASN1_STRING_get0_data(msg),
                    ASN1_STRING_length(msg), 4);

    return 1;
}