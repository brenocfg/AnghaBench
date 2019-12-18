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
struct ipc_params {scalar_t__ key; } ;
struct ipc_ops {int dummy; } ;
struct ipc_namespace {int dummy; } ;
struct ipc_ids {int dummy; } ;

/* Variables and functions */
 scalar_t__ IPC_PRIVATE ; 
 int ipcget_new (struct ipc_namespace*,struct ipc_ids*,struct ipc_ops const*,struct ipc_params*) ; 
 int ipcget_public (struct ipc_namespace*,struct ipc_ids*,struct ipc_ops const*,struct ipc_params*) ; 

int ipcget(struct ipc_namespace *ns, struct ipc_ids *ids,
			const struct ipc_ops *ops, struct ipc_params *params)
{
	if (params->key == IPC_PRIVATE)
		return ipcget_new(ns, ids, ops, params);
	else
		return ipcget_public(ns, ids, ops, params);
}