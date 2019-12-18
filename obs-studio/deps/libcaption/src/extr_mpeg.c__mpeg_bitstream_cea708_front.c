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
typedef  int /*<<< orphan*/  mpeg_bitstream_t ;
typedef  int /*<<< orphan*/  cea708_t ;

/* Variables and functions */
 int /*<<< orphan*/ * _mpeg_bitstream_cea708_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

cea708_t* _mpeg_bitstream_cea708_front(mpeg_bitstream_t* packet) { return _mpeg_bitstream_cea708_at(packet, 0); }