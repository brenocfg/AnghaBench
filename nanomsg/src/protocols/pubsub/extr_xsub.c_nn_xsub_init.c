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
struct nn_xsub {int /*<<< orphan*/  trie; int /*<<< orphan*/  fq; int /*<<< orphan*/  sockbase; } ;
struct nn_sockbase_vfptr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_fq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_sockbase_init (int /*<<< orphan*/ *,struct nn_sockbase_vfptr const*,void*) ; 
 int /*<<< orphan*/  nn_trie_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nn_xsub_init (struct nn_xsub *self,
    const struct nn_sockbase_vfptr *vfptr, void *hint)
{
    nn_sockbase_init (&self->sockbase, vfptr, hint);
    nn_fq_init (&self->fq);
    nn_trie_init (&self->trie);
}