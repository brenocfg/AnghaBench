#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * indices; } ;
typedef  TYPE_1__ php_com_saproxy ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_DUP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void clone_indices(php_com_saproxy *dest, php_com_saproxy *src, int ndims)
{
	int i;

	for (i = 0; i < ndims; i++) {
		ZVAL_DUP(&dest->indices[i], &src->indices[i]);
	}
}