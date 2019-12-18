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
struct TYPE_3__ {int /*<<< orphan*/  name_id; int /*<<< orphan*/  prov; } ;
typedef  TYPE_1__ EVP_MAC ;

/* Variables and functions */
 int evp_is_a (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

int EVP_MAC_is_a(const EVP_MAC *mac, const char *name)
{
    return evp_is_a(mac->prov, mac->name_id, name);
}