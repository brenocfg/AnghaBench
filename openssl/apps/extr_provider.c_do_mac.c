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
typedef  int /*<<< orphan*/  EVP_MAC ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MAC_gettable_ctx_params (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_gettable_params (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_settable_ctx_params (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  collect_mac_names ; 
 int /*<<< orphan*/  do_method (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void do_mac(EVP_MAC *mac, void *meta)
{
    do_method(mac, collect_mac_names,
              EVP_MAC_gettable_params(mac),
              EVP_MAC_gettable_ctx_params(mac),
              EVP_MAC_settable_ctx_params(mac),
              meta);
}