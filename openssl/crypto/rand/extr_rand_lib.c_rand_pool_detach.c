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
struct TYPE_3__ {unsigned char* buffer; scalar_t__ entropy; } ;
typedef  TYPE_1__ RAND_POOL ;

/* Variables and functions */

unsigned char *rand_pool_detach(RAND_POOL *pool)
{
    unsigned char *ret = pool->buffer;
    pool->buffer = NULL;
    pool->entropy = 0;
    return ret;
}