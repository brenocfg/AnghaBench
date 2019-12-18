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
struct cbuf {int mask; scalar_t__ len; scalar_t__ base; } ;

/* Variables and functions */

__attribute__((used)) static void cbuf_init(struct cbuf *cb, int size)
{
	cb->base = cb->len = 0;
	cb->mask = size-1;
}