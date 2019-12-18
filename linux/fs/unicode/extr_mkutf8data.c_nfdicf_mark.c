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
struct unicode_data {scalar_t__ utf8nfdicf; } ;

/* Variables and functions */

__attribute__((used)) static int nfdicf_mark(void *l)
{
	struct unicode_data *leaf = l;

	if (leaf->utf8nfdicf)
		return 1;
	return 0;
}