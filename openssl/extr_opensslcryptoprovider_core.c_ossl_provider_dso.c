#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  const* module; } ;
typedef  TYPE_1__ OSSL_PROVIDER ;
typedef  int /*<<< orphan*/  DSO ;

/* Variables and functions */

const DSO *ossl_provider_dso(OSSL_PROVIDER *prov)
{
    return prov->module;
}