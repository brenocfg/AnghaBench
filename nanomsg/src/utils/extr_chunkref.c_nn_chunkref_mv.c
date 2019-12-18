#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nn_chunkref_chunk {int dummy; } ;
struct TYPE_2__ {int* ref; } ;
struct nn_chunkref {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct nn_chunkref*,struct nn_chunkref*,int) ; 

void nn_chunkref_mv (struct nn_chunkref *dst, struct nn_chunkref *src)
{
    memcpy (dst, src, src->u.ref [0] == 0xff ?
        (int)sizeof (struct nn_chunkref_chunk) : src->u.ref [0] + 1);
}