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
struct TYPE_2__ {unsigned char* buf; unsigned char* buf2; size_t sigsize; int /*<<< orphan*/ ** sm2_pkey; int /*<<< orphan*/ ** sm2_vfy_ctx; } ;
typedef  TYPE_1__ loopargs_t ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ COND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int EVP_DigestVerify (int /*<<< orphan*/ *,unsigned char*,size_t,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_DigestVerifyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_sm3 () ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ ** sm2_c ; 
 size_t testnum ; 

__attribute__((used)) static int SM2_verify_loop(void *args)
{
    loopargs_t *tempargs = *(loopargs_t **) args;
    unsigned char *buf = tempargs->buf;
    EVP_MD_CTX **sm2ctx = tempargs->sm2_vfy_ctx;
    unsigned char *sm2sig = tempargs->buf2;
    size_t sm2sigsize = tempargs->sigsize;
    int ret, count;
    EVP_PKEY **sm2_pkey = tempargs->sm2_pkey;

    for (count = 0; COND(sm2_c[testnum][1]); count++) {
        if (!EVP_DigestVerifyInit(sm2ctx[testnum], NULL, EVP_sm3(),
                                  NULL, sm2_pkey[testnum])) {
            BIO_printf(bio_err, "SM2 verify init failure\n");
            ERR_print_errors(bio_err);
            count = -1;
            break;
        }
        ret = EVP_DigestVerify(sm2ctx[testnum], sm2sig, sm2sigsize,
                               buf, 20);
        if (ret != 1) {
            BIO_printf(bio_err, "SM2 verify failure\n");
            ERR_print_errors(bio_err);
            count = -1;
            break;
        }
    }
    return count;
}