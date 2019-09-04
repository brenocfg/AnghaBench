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
typedef  int /*<<< orphan*/  u16 ;
struct controller {scalar_t__ creg; } ;

/* Variables and functions */
 int /*<<< orphan*/  readw (scalar_t__) ; 

__attribute__((used)) static inline u16 shpc_readw(struct controller *ctrl, int reg)
{
	return readw(ctrl->creg + reg);
}