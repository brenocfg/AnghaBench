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
struct dstr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 

__attribute__((used)) static inline void dstr_array_free(struct dstr *array, const size_t count)
{
	size_t i;
	for (i = 0; i < count; i++)
		dstr_free(array + i);
}