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
struct TYPE_5__ {int /*<<< orphan*/  fetched_digest; int /*<<< orphan*/  output; int /*<<< orphan*/  input; } ;
struct TYPE_4__ {TYPE_2__* data; } ;
typedef  TYPE_1__ EVP_TEST ;
typedef  TYPE_2__ DIGEST_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_meth_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evp_test_buffer_free ; 
 int /*<<< orphan*/  sk_EVP_TEST_BUFFER_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void digest_test_cleanup(EVP_TEST *t)
{
    DIGEST_DATA *mdat = t->data;

    sk_EVP_TEST_BUFFER_pop_free(mdat->input, evp_test_buffer_free);
    OPENSSL_free(mdat->output);
    EVP_MD_meth_free(mdat->fetched_digest);
}