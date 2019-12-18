#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t num; scalar_t__ array; } ;
struct decl_info {int /*<<< orphan*/  name; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_free (TYPE_1__) ; 
 int /*<<< orphan*/  decl_param_free (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct decl_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void decl_info_free(struct decl_info *decl)
{
	if (decl) {
		for (size_t i = 0; i < decl->params.num; i++)
			decl_param_free(decl->params.array + i);
		da_free(decl->params);

		bfree(decl->name);
		memset(decl, 0, sizeof(struct decl_info));
	}
}