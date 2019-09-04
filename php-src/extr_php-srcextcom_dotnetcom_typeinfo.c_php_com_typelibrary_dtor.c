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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  ITypeLib ;

/* Variables and functions */
 int /*<<< orphan*/  ITypeLib_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_PTR_P (int /*<<< orphan*/ *) ; 

void php_com_typelibrary_dtor(zval *pDest)
{
	ITypeLib *Lib = (ITypeLib*)Z_PTR_P(pDest);
	ITypeLib_Release(Lib);
}