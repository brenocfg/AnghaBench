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
 int /*<<< orphan*/  pair (char const*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  r_str_bool (int) ; 

__attribute__((used)) static void pair_bool(const char *key, bool val, int mode, bool last) {
	pair (key, r_str_bool (val), mode, last);
}