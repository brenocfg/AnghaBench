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
struct TYPE_3__ {int /*<<< orphan*/  status; scalar_t__ latent; scalar_t__ front; scalar_t__ size; scalar_t__ cts; scalar_t__ dts; } ;
typedef  TYPE_1__ mpeg_bitstream_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIBCAPTION_OK ; 

void mpeg_bitstream_init(mpeg_bitstream_t* packet)
{
    packet->dts = 0;
    packet->cts = 0;
    packet->size = 0;
    packet->front = 0;
    packet->latent = 0;
    packet->status = LIBCAPTION_OK;
}