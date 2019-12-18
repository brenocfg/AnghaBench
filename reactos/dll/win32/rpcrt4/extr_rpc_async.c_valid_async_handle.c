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
struct TYPE_3__ {scalar_t__ Signature; } ;
typedef  TYPE_1__* PRPC_ASYNC_STATE ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ RPC_ASYNC_SIGNATURE ; 

__attribute__((used)) static inline BOOL valid_async_handle(PRPC_ASYNC_STATE pAsync)
{
    return pAsync->Signature == RPC_ASYNC_SIGNATURE;
}