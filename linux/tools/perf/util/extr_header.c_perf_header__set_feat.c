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
struct perf_header {int /*<<< orphan*/  adds_features; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

void perf_header__set_feat(struct perf_header *header, int feat)
{
	set_bit(feat, header->adds_features);
}