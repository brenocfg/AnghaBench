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
struct nn_msg {int /*<<< orphan*/  body; int /*<<< orphan*/  hdrs; int /*<<< orphan*/  sphdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_chunkref_init (int /*<<< orphan*/ *,size_t) ; 

void nn_msg_init (struct nn_msg *self, size_t size)
{
    nn_chunkref_init (&self->sphdr, 0);
    nn_chunkref_init (&self->hdrs, 0);
    nn_chunkref_init (&self->body, size);
}