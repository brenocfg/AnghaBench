#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  OPENSSL_LHASH ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_file () ; 
 int /*<<< orphan*/  BIO_set_fp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_LH_node_stats_bio (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

void OPENSSL_LH_node_stats(const OPENSSL_LHASH *lh, FILE *fp)
{
    BIO *bp;

    bp = BIO_new(BIO_s_file());
    if (bp == NULL)
        return;
    BIO_set_fp(bp, fp, BIO_NOCLOSE);
    OPENSSL_LH_node_stats_bio(lh, bp);
    BIO_free(bp);
}