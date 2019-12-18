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
struct btf_ext {struct btf_ext* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct btf_ext*) ; 

void btf_ext__free(struct btf_ext *btf_ext)
{
	if (!btf_ext)
		return;
	free(btf_ext->data);
	free(btf_ext);
}