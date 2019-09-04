#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {int length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_free (TYPE_1__*) ; 
 TYPE_1__* ASN1_INTEGER_new () ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ ) ; 
 scalar_t__ RAND_bytes (unsigned char*,int) ; 
 int /*<<< orphan*/  app_malloc (int,char*) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static ASN1_INTEGER *create_nonce(int bits)
{
    unsigned char buf[20];
    ASN1_INTEGER *nonce = NULL;
    int len = (bits - 1) / 8 + 1;
    int i;

    if (len > (int)sizeof(buf))
        goto err;
    if (RAND_bytes(buf, len) <= 0)
        goto err;

    /* Find the first non-zero byte and creating ASN1_INTEGER object. */
    for (i = 0; i < len && !buf[i]; ++i)
        continue;
    if ((nonce = ASN1_INTEGER_new()) == NULL)
        goto err;
    OPENSSL_free(nonce->data);
    nonce->length = len - i;
    nonce->data = app_malloc(nonce->length + 1, "nonce buffer");
    memcpy(nonce->data, buf + i, nonce->length);
    return nonce;

 err:
    BIO_printf(bio_err, "could not create nonce\n");
    ASN1_INTEGER_free(nonce);
    return NULL;
}