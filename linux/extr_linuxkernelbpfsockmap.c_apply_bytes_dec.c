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
struct smap_psock {int apply_bytes; } ;

/* Variables and functions */

__attribute__((used)) static void apply_bytes_dec(struct smap_psock *psock, int i)
{
	if (psock->apply_bytes) {
		if (psock->apply_bytes < i)
			psock->apply_bytes = 0;
		else
			psock->apply_bytes -= i;
	}
}