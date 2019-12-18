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
struct nn_xsub {int /*<<< orphan*/  sockbase; int /*<<< orphan*/  fq; int /*<<< orphan*/  trie; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_fq_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_sockbase_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_trie_term (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nn_xsub_term (struct nn_xsub *self)
{
    nn_trie_term (&self->trie);
    nn_fq_term (&self->fq);
    nn_sockbase_term (&self->sockbase);
}