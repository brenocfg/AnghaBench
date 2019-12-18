#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  data; scalar_t__ length; } ;
struct TYPE_8__ {int /*<<< orphan*/ * algorithm; } ;
struct TYPE_10__ {TYPE_3__* signature; TYPE_2__ sig_algor; TYPE_1__* spkac; } ;
struct TYPE_9__ {int length; scalar_t__ data; } ;
struct TYPE_7__ {TYPE_5__* challenge; int /*<<< orphan*/  pubkey; } ;
typedef  TYPE_4__ NETSCAPE_SPKI ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;
typedef  TYPE_5__ ASN1_IA5STRING ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_print_public (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int NID_undef ; 
 char* OBJ_nid2ln (int) ; 
 int OBJ_obj2nid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_PUBKEY_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_PUBKEY_get0_param (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int NETSCAPE_SPKI_print(BIO *out, NETSCAPE_SPKI *spki)
{
    EVP_PKEY *pkey;
    ASN1_IA5STRING *chal;
    ASN1_OBJECT *spkioid;
    int i, n;
    char *s;
    BIO_printf(out, "Netscape SPKI:\n");
    X509_PUBKEY_get0_param(&spkioid, NULL, NULL, NULL, spki->spkac->pubkey);
    i = OBJ_obj2nid(spkioid);
    BIO_printf(out, "  Public Key Algorithm: %s\n",
               (i == NID_undef) ? "UNKNOWN" : OBJ_nid2ln(i));
    pkey = X509_PUBKEY_get(spki->spkac->pubkey);
    if (pkey == NULL)
        BIO_printf(out, "  Unable to load public key\n");
    else {
        EVP_PKEY_print_public(out, pkey, 4, NULL);
        EVP_PKEY_free(pkey);
    }
    chal = spki->spkac->challenge;
    if (chal->length)
        BIO_printf(out, "  Challenge String: %s\n", chal->data);
    i = OBJ_obj2nid(spki->sig_algor.algorithm);
    BIO_printf(out, "  Signature Algorithm: %s",
               (i == NID_undef) ? "UNKNOWN" : OBJ_nid2ln(i));

    n = spki->signature->length;
    s = (char *)spki->signature->data;
    for (i = 0; i < n; i++) {
        if ((i % 18) == 0)
            BIO_write(out, "\n      ", 7);
        BIO_printf(out, "%02x%s", (unsigned char)s[i],
                   ((i + 1) == n) ? "" : ":");
    }
    BIO_write(out, "\n", 1);
    return 1;
}