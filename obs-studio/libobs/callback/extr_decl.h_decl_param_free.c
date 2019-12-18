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
struct decl_param {scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct decl_param*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void decl_param_free(struct decl_param *param)
{
	if (param->name)
		bfree(param->name);
	memset(param, 0, sizeof(struct decl_param));
}