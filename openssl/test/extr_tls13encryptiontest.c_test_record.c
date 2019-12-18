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
struct TYPE_6__ {int /*<<< orphan*/  plaintext; int /*<<< orphan*/  ciphertext; } ;
struct TYPE_5__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ SSL3_RECORD ;
typedef  TYPE_2__ RECORD_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  TEST_info (char*) ; 
 int /*<<< orphan*/  TEST_mem_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  TEST_ptr (unsigned char*) ; 
 unsigned char* multihexstr2buf (int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int test_record(SSL3_RECORD *rec, RECORD_DATA *recd, int enc)
{
    int ret = 0;
    unsigned char *refd;
    size_t refdatalen;

    if (enc)
        refd = multihexstr2buf(recd->ciphertext, &refdatalen);
    else
        refd = multihexstr2buf(recd->plaintext, &refdatalen);

    if (!TEST_ptr(refd)) {
        TEST_info("Failed to get reference data");
        goto err;
    }

    if (!TEST_mem_eq(rec->data, rec->length, refd, refdatalen))
        goto err;

    ret = 1;

 err:
    OPENSSL_free(refd);
    return ret;
}