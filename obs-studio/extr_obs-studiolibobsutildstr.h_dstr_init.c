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
struct dstr {scalar_t__ capacity; scalar_t__ len; int /*<<< orphan*/ * array; } ;

/* Variables and functions */

__attribute__((used)) static inline void dstr_init(struct dstr *dst)
{
	dst->array    = NULL;
	dst->len      = 0;
	dst->capacity = 0;
}