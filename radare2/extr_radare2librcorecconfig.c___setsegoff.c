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
typedef  int /*<<< orphan*/  RConfig ;

/* Variables and functions */
 int /*<<< orphan*/  r_config_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_str_bool (int) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static inline void __setsegoff(RConfig *cfg, const char *asmarch, int asmbits) {
	int autoseg = (!strncmp (asmarch, "x86", 3) && asmbits == 16);
	r_config_set (cfg, "asm.segoff", r_str_bool (autoseg));
}