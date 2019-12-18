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
 int /*<<< orphan*/  dstr_ncat (struct dstr*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static inline void dstr_cat(struct dstr *dst, const char *array)
{
	size_t len;
	if (!array || !*array)
		return;

	len = strlen(array);
	dstr_ncat(dst, array, len);
}