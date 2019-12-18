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
struct azx {scalar_t__ snoop; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_X86 ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool azx_snoop(struct azx *chip)
{
	return !IS_ENABLED(CONFIG_X86) || chip->snoop;
}