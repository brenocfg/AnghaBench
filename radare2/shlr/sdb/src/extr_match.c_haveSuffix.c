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

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static inline int haveSuffix(const char *glob, int glob_len, const char *sfx) {
	const int sfx_len = strlen (sfx);
	return (glob_len>sfx_len && !strcmp (glob+glob_len-sfx_len, sfx));
}