#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int num_nodes; TYPE_1__** b; } ;
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ OPENSSL_LH_NODE ;
typedef  TYPE_2__ OPENSSL_LHASH ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,unsigned int,unsigned int) ; 

void OPENSSL_LH_node_stats_bio(const OPENSSL_LHASH *lh, BIO *out)
{
    OPENSSL_LH_NODE *n;
    unsigned int i, num;

    for (i = 0; i < lh->num_nodes; i++) {
        for (n = lh->b[i], num = 0; n != NULL; n = n->next)
            num++;
        BIO_printf(out, "node %6u -> %3u\n", i, num);
    }
}