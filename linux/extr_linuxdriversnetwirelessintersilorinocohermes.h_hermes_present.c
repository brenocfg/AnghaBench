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
struct hermes {int dummy; } ;

/* Variables and functions */
 scalar_t__ HERMES_MAGIC ; 
 int /*<<< orphan*/  SWSUPPORT0 ; 
 scalar_t__ hermes_read_regn (struct hermes*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int hermes_present(struct hermes *hw)
{
	return hermes_read_regn(hw, SWSUPPORT0) == HERMES_MAGIC;
}