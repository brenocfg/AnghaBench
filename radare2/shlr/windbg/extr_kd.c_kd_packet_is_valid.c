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
struct TYPE_3__ {scalar_t__ leader; } ;
typedef  TYPE_1__ kd_packet_t ;

/* Variables and functions */
 scalar_t__ KD_PACKET_CTRL ; 
 scalar_t__ KD_PACKET_DATA ; 

int kd_packet_is_valid(const kd_packet_t *p) {
	return p->leader == KD_PACKET_CTRL || p->leader == KD_PACKET_DATA;
}