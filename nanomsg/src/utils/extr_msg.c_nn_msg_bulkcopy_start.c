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
typedef  int /*<<< orphan*/  uint32_t ;
struct nn_msg {int /*<<< orphan*/  body; int /*<<< orphan*/  hdrs; int /*<<< orphan*/  sphdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_chunkref_bulkcopy_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void nn_msg_bulkcopy_start (struct nn_msg *self, uint32_t copies)
{
    nn_chunkref_bulkcopy_start (&self->sphdr, copies);
    nn_chunkref_bulkcopy_start (&self->hdrs, copies);
    nn_chunkref_bulkcopy_start (&self->body, copies);
}