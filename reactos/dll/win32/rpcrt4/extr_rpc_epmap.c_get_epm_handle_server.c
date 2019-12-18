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
typedef  int /*<<< orphan*/  RPC_STATUS ;
typedef  int /*<<< orphan*/  RPC_BINDING_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  RpcBindingFromStringBindingA (unsigned char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static RPC_STATUS get_epm_handle_server(RPC_BINDING_HANDLE *epm_handle)
{
    unsigned char string_binding[] = "ncacn_np:.[\\\\pipe\\\\epmapper]";

    return RpcBindingFromStringBindingA(string_binding, epm_handle);
}