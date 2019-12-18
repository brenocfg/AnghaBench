#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  latent; } ;
typedef  TYPE_1__ mpeg_bitstream_t ;
typedef  int /*<<< orphan*/  cea708_t ;

/* Variables and functions */
 int /*<<< orphan*/ * _mpeg_bitstream_cea708_back (TYPE_1__*) ; 
 int /*<<< orphan*/  cea708_init (int /*<<< orphan*/ *,double) ; 

cea708_t* _mpeg_bitstream_cea708_emplace_back(mpeg_bitstream_t* packet, double timestamp)
{
    ++packet->latent;
    cea708_t* cea708 = _mpeg_bitstream_cea708_back(packet);
    cea708_init(cea708, timestamp);
    return cea708;
}