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
struct TYPE_2__ {unsigned char* buf; unsigned char* buf2; unsigned int siglen; int /*<<< orphan*/ ** ecdsa; } ;
typedef  TYPE_1__ loopargs_t ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ COND (int /*<<< orphan*/ ) ; 
 int ECDSA_sign (int /*<<< orphan*/ ,unsigned char*,int,unsigned char*,unsigned int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ ** ecdsa_c ; 
 size_t testnum ; 

__attribute__((used)) static int ECDSA_sign_loop(void *args)
{
    loopargs_t *tempargs = *(loopargs_t **) args;
    unsigned char *buf = tempargs->buf;
    EC_KEY **ecdsa = tempargs->ecdsa;
    unsigned char *ecdsasig = tempargs->buf2;
    unsigned int *ecdsasiglen = &tempargs->siglen;
    int ret, count;
    for (count = 0; COND(ecdsa_c[testnum][0]); count++) {
        ret = ECDSA_sign(0, buf, 20, ecdsasig, ecdsasiglen, ecdsa[testnum]);
        if (ret == 0) {
            BIO_printf(bio_err, "ECDSA sign failure\n");
            ERR_print_errors(bio_err);
            count = -1;
            break;
        }
    }
    return count;
}