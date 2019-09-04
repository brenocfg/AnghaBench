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
typedef  scalar_t__ ut64 ;
struct TYPE_3__ {scalar_t__ screen; scalar_t__ screen_size; } ;
typedef  TYPE_1__ BfvmCPU ;

/* Variables and functions */

__attribute__((used)) static inline int is_in_screen(ut64 off, BfvmCPU *c) {
	return (off >= c->screen && off < c->screen+c->screen_size);
}