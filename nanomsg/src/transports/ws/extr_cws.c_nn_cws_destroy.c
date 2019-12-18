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
struct nn_cws {int /*<<< orphan*/  fsm; int /*<<< orphan*/  usock; int /*<<< orphan*/  retry; int /*<<< orphan*/  sws; int /*<<< orphan*/  dns; int /*<<< orphan*/  nic; int /*<<< orphan*/  remote_host; int /*<<< orphan*/  resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_backoff_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_chunkref_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_dns_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_free (struct nn_cws*) ; 
 int /*<<< orphan*/  nn_fsm_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_sws_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_usock_term (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nn_cws_destroy (void *self)
{
    struct nn_cws *cws = self;

    nn_chunkref_term (&cws->resource);
    nn_chunkref_term (&cws->remote_host);
    nn_chunkref_term (&cws->nic);
    nn_dns_term (&cws->dns);
    nn_sws_term (&cws->sws);
    nn_backoff_term (&cws->retry);
    nn_usock_term (&cws->usock);
    nn_fsm_term (&cws->fsm);

    nn_free (cws);
}