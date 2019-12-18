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
struct TYPE_3__ {size_t front; int /*<<< orphan*/ * cea708; } ;
typedef  TYPE_1__ mpeg_bitstream_t ;
typedef  int /*<<< orphan*/  cea708_t ;

/* Variables and functions */
 size_t MAX_REFRENCE_FRAMES ; 

cea708_t* _mpeg_bitstream_cea708_at(mpeg_bitstream_t* packet, size_t pos) { return &packet->cea708[(packet->front + pos) % MAX_REFRENCE_FRAMES]; }