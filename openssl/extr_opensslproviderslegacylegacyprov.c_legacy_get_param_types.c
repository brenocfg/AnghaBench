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
typedef  int /*<<< orphan*/  OSSL_PROVIDER ;
typedef  int /*<<< orphan*/  OSSL_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  const* legacy_param_types ; 

__attribute__((used)) static const OSSL_ITEM *legacy_get_param_types(const OSSL_PROVIDER *prov)
{
    return legacy_param_types;
}