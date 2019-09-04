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
struct xxh64_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct xxh64_state*,struct xxh64_state const*,int) ; 

void xxh64_copy_state(struct xxh64_state *dst, const struct xxh64_state *src)
{
	memcpy(dst, src, sizeof(*dst));
}