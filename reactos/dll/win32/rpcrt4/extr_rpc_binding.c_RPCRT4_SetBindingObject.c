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
typedef  int /*<<< orphan*/  UUID ;
struct TYPE_4__ {int /*<<< orphan*/  ObjectUuid; } ;
typedef  TYPE_1__ RpcBinding ;
typedef  int /*<<< orphan*/  RPC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UuidCreateNil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/  const*) ; 

RPC_STATUS RPCRT4_SetBindingObject(RpcBinding* Binding, const UUID* ObjectUuid)
{
  TRACE("(*RpcBinding == ^%p, UUID == %s)\n", Binding, debugstr_guid(ObjectUuid)); 
  if (ObjectUuid) Binding->ObjectUuid = *ObjectUuid;
  else UuidCreateNil(&Binding->ObjectUuid);
  return RPC_S_OK;
}