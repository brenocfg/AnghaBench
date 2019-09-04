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
struct TYPE_4__ {scalar_t__ latent; } ;
typedef  TYPE_1__ mpeg_bitstream_t ;
typedef  int /*<<< orphan*/  cea708_t ;

/* Variables and functions */
 int /*<<< orphan*/ * _mpeg_bitstream_cea708_at (TYPE_1__*,scalar_t__) ; 

cea708_t* _mpeg_bitstream_cea708_back(mpeg_bitstream_t* packet) { return _mpeg_bitstream_cea708_at(packet, packet->latent - 1); }