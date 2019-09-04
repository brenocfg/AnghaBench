#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int pad_type; } ;
typedef  TYPE_1__ MDC2_CTX ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_MD_CTX_md_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_mdc2 () ; 
 int MDC2_DIGEST_LENGTH ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pad1 ; 
 int /*<<< orphan*/  pad2 ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int test_mdc2(void)
{
    int testresult = 0;
    unsigned char md[MDC2_DIGEST_LENGTH];
    EVP_MD_CTX *c;
    static char text[] = "Now is the time for all ";
    size_t tlen = strlen(text);

# ifdef CHARSET_EBCDIC
    ebcdic2ascii(text, text, tlen);
# endif

    c = EVP_MD_CTX_new();
    if (!TEST_ptr(c)
        || !TEST_true(EVP_DigestInit_ex(c, EVP_mdc2(), NULL))
        || !TEST_true(EVP_DigestUpdate(c, (unsigned char *)text, tlen))
        || !TEST_true(EVP_DigestFinal_ex(c, &(md[0]), NULL))
        || !TEST_mem_eq(md, MDC2_DIGEST_LENGTH, pad1, MDC2_DIGEST_LENGTH)
        || !TEST_true(EVP_DigestInit_ex(c, EVP_mdc2(), NULL)))
        goto end;

    /* FIXME: use a ctl function? */
    ((MDC2_CTX *)EVP_MD_CTX_md_data(c))->pad_type = 2;
    if (!TEST_true(EVP_DigestUpdate(c, (unsigned char *)text, tlen))
        || !TEST_true(EVP_DigestFinal_ex(c, &(md[0]), NULL))
        || !TEST_mem_eq(md, MDC2_DIGEST_LENGTH, pad2, MDC2_DIGEST_LENGTH))
        goto end;

    testresult = 1;
 end:
    EVP_MD_CTX_free(c);
    return testresult;
}