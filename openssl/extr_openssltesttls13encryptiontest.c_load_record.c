#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  plaintext; int /*<<< orphan*/  seq; int /*<<< orphan*/  iv; int /*<<< orphan*/  key; } ;
struct TYPE_5__ {unsigned char* data; unsigned char* input; size_t length; } ;
typedef  TYPE_1__ SSL3_RECORD ;
typedef  TYPE_2__ RECORD_DATA ;

/* Variables and functions */
 scalar_t__ EVP_GCM_TLS_TAG_LEN ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_hexstr2buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned char* OPENSSL_malloc (scalar_t__) ; 
 size_t SEQ_NUM_SIZE ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 unsigned char* multihexstr2buf (int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int load_record(SSL3_RECORD *rec, RECORD_DATA *recd, unsigned char **key,
                       unsigned char *iv, size_t ivlen, unsigned char *seq)
{
    unsigned char *pt = NULL, *sq = NULL, *ivtmp = NULL;
    size_t ptlen;

    *key = OPENSSL_hexstr2buf(recd->key, NULL);
    ivtmp = OPENSSL_hexstr2buf(recd->iv, NULL);
    sq = OPENSSL_hexstr2buf(recd->seq, NULL);
    pt = multihexstr2buf(recd->plaintext, &ptlen);

    if (*key == NULL || ivtmp == NULL || sq == NULL || pt == NULL)
        goto err;

    rec->data = rec->input = OPENSSL_malloc(ptlen + EVP_GCM_TLS_TAG_LEN);

    if (rec->data == NULL)
        goto err;

    rec->length = ptlen;
    memcpy(rec->data, pt, ptlen);
    OPENSSL_free(pt);
    memcpy(seq, sq, SEQ_NUM_SIZE);
    OPENSSL_free(sq);
    memcpy(iv, ivtmp, ivlen);
    OPENSSL_free(ivtmp);

    return 1;
 err:
    OPENSSL_free(*key);
    *key = NULL;
    OPENSSL_free(ivtmp);
    OPENSSL_free(sq);
    OPENSSL_free(pt);
    return 0;
}