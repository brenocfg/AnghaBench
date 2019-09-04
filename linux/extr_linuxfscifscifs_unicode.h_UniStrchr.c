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
typedef  scalar_t__ const wchar_t ;

/* Variables and functions */

__attribute__((used)) static inline wchar_t *
UniStrchr(const wchar_t *ucs, wchar_t uc)
{
	while ((*ucs != uc) && *ucs)
		ucs++;

	if (*ucs == uc)
		return (wchar_t *) ucs;
	return NULL;
}