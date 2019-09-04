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
struct TYPE_3__ {int /*<<< orphan*/  num_hash_comps; int /*<<< orphan*/  num_retrieve_miss; int /*<<< orphan*/  num_retrieve; int /*<<< orphan*/  num_no_delete; int /*<<< orphan*/  num_delete; int /*<<< orphan*/  num_replace; int /*<<< orphan*/  num_insert; int /*<<< orphan*/  num_comp_calls; int /*<<< orphan*/  num_hash_calls; int /*<<< orphan*/  num_contract_reallocs; int /*<<< orphan*/  num_contracts; int /*<<< orphan*/  num_expand_reallocs; int /*<<< orphan*/  num_expands; int /*<<< orphan*/  num_alloc_nodes; int /*<<< orphan*/  num_nodes; int /*<<< orphan*/  num_items; } ;
typedef  TYPE_1__ OPENSSL_LHASH ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OPENSSL_LH_stats_bio(const OPENSSL_LHASH *lh, BIO *out)
{
    BIO_printf(out, "num_items             = %lu\n", lh->num_items);
    BIO_printf(out, "num_nodes             = %u\n",  lh->num_nodes);
    BIO_printf(out, "num_alloc_nodes       = %u\n",  lh->num_alloc_nodes);
    BIO_printf(out, "num_expands           = %lu\n", lh->num_expands);
    BIO_printf(out, "num_expand_reallocs   = %lu\n", lh->num_expand_reallocs);
    BIO_printf(out, "num_contracts         = %lu\n", lh->num_contracts);
    BIO_printf(out, "num_contract_reallocs = %lu\n", lh->num_contract_reallocs);
    BIO_printf(out, "num_hash_calls        = %lu\n", lh->num_hash_calls);
    BIO_printf(out, "num_comp_calls        = %lu\n", lh->num_comp_calls);
    BIO_printf(out, "num_insert            = %lu\n", lh->num_insert);
    BIO_printf(out, "num_replace           = %lu\n", lh->num_replace);
    BIO_printf(out, "num_delete            = %lu\n", lh->num_delete);
    BIO_printf(out, "num_no_delete         = %lu\n", lh->num_no_delete);
    BIO_printf(out, "num_retrieve          = %lu\n", lh->num_retrieve);
    BIO_printf(out, "num_retrieve_miss     = %lu\n", lh->num_retrieve_miss);
    BIO_printf(out, "num_hash_comps        = %lu\n", lh->num_hash_comps);
}