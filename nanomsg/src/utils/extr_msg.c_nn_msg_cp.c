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
 int /*<<< orphan*/  nn_chunkref_cp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void nn_msg_cp (struct nn_msg *dst, struct nn_msg *src)
{
    nn_chunkref_cp (&dst->sphdr, &src->sphdr);
    nn_chunkref_cp (&dst->hdrs, &src->hdrs);
    nn_chunkref_cp (&dst->body, &src->body);
}