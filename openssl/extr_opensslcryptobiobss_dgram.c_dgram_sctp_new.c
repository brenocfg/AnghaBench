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
typedef  int /*<<< orphan*/  bio_dgram_sctp_data ;
struct TYPE_3__ {scalar_t__ flags; int /*<<< orphan*/ * ptr; scalar_t__ num; scalar_t__ init; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_F_DGRAM_SCTP_NEW ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/ * OPENSSL_zalloc (int) ; 

__attribute__((used)) static int dgram_sctp_new(BIO *bi)
{
    bio_dgram_sctp_data *data = NULL;

    bi->init = 0;
    bi->num = 0;
    if ((data = OPENSSL_zalloc(sizeof(*data))) == NULL) {
        BIOerr(BIO_F_DGRAM_SCTP_NEW, ERR_R_MALLOC_FAILURE);
        return 0;
    }
#  ifdef SCTP_PR_SCTP_NONE
    data->prinfo.pr_policy = SCTP_PR_SCTP_NONE;
#  endif
    bi->ptr = data;

    bi->flags = 0;
    return 1;
}