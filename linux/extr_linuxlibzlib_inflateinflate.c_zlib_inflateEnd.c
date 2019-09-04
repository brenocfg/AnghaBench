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
typedef  TYPE_1__* z_streamp ;
struct TYPE_3__ {int /*<<< orphan*/ * state; } ;

/* Variables and functions */
 int Z_OK ; 
 int Z_STREAM_ERROR ; 

int zlib_inflateEnd(z_streamp strm)
{
    if (strm == NULL || strm->state == NULL)
        return Z_STREAM_ERROR;
    return Z_OK;
}