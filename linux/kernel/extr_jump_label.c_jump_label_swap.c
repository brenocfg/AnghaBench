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
struct jump_entry {scalar_t__ key; scalar_t__ target; scalar_t__ code; } ;

/* Variables and functions */

__attribute__((used)) static void jump_label_swap(void *a, void *b, int size)
{
	long delta = (unsigned long)a - (unsigned long)b;
	struct jump_entry *jea = a;
	struct jump_entry *jeb = b;
	struct jump_entry tmp = *jea;

	jea->code	= jeb->code - delta;
	jea->target	= jeb->target - delta;
	jea->key	= jeb->key - delta;

	jeb->code	= tmp.code + delta;
	jeb->target	= tmp.target + delta;
	jeb->key	= tmp.key + delta;
}