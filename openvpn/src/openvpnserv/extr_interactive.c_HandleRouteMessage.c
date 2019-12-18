#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * undo_lists_t ;
struct TYPE_17__ {int index; int /*<<< orphan*/  name; } ;
struct TYPE_15__ {scalar_t__ type; } ;
struct TYPE_18__ {TYPE_3__ iface; int /*<<< orphan*/  gateway; int /*<<< orphan*/  family; scalar_t__ prefix_len; int /*<<< orphan*/  prefix; int /*<<< orphan*/  metric; TYPE_1__ header; } ;
typedef  TYPE_4__ route_message_t ;
typedef  scalar_t__ UINT8 ;
struct TYPE_16__ {scalar_t__ PrefixLength; void* Prefix; } ;
struct TYPE_19__ {int ValidLifetime; int PreferredLifetime; int InterfaceIndex; int /*<<< orphan*/  InterfaceLuid; void* NextHop; TYPE_2__ DestinationPrefix; int /*<<< orphan*/  Metric; int /*<<< orphan*/  Protocol; } ;
typedef  TYPE_5__* PMIB_IPFORWARD_ROW2 ;
typedef  int /*<<< orphan*/  NET_LUID ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ AddListItem (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  CmpRoute ; 
 scalar_t__ CreateIpForwardEntry2 (TYPE_5__*) ; 
 scalar_t__ DeleteRoute (TYPE_5__*) ; 
 scalar_t__ ERROR_OUTOFMEMORY ; 
 scalar_t__ InterfaceLuid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MIB_IPPROTO_NETMGMT ; 
 TYPE_5__* RemoveListItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_5__*,int) ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 TYPE_5__* malloc (int) ; 
 scalar_t__ msg_add_route ; 
 size_t route ; 
 void* sockaddr_inet (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD
HandleRouteMessage(route_message_t *msg, undo_lists_t *lists)
{
    DWORD err;
    PMIB_IPFORWARD_ROW2 fwd_row;
    BOOL add = msg->header.type == msg_add_route;

    fwd_row = malloc(sizeof(*fwd_row));
    if (fwd_row == NULL)
    {
        return ERROR_OUTOFMEMORY;
    }

    ZeroMemory(fwd_row, sizeof(*fwd_row));
    fwd_row->ValidLifetime = 0xffffffff;
    fwd_row->PreferredLifetime = 0xffffffff;
    fwd_row->Protocol = MIB_IPPROTO_NETMGMT;
    fwd_row->Metric = msg->metric;
    fwd_row->DestinationPrefix.Prefix = sockaddr_inet(msg->family, &msg->prefix);
    fwd_row->DestinationPrefix.PrefixLength = (UINT8) msg->prefix_len;
    fwd_row->NextHop = sockaddr_inet(msg->family, &msg->gateway);

    if (msg->iface.index != -1)
    {
        fwd_row->InterfaceIndex = msg->iface.index;
    }
    else if (strlen(msg->iface.name))
    {
        NET_LUID luid;
        err = InterfaceLuid(msg->iface.name, &luid);
        if (err)
        {
            goto out;
        }
        fwd_row->InterfaceLuid = luid;
    }

    if (add)
    {
        err = CreateIpForwardEntry2(fwd_row);
        if (err)
        {
            goto out;
        }

        err = AddListItem(&(*lists)[route], fwd_row);
        if (err)
        {
            DeleteRoute(fwd_row);
        }
    }
    else
    {
        err = DeleteRoute(fwd_row);
        if (err)
        {
            goto out;
        }

        free(RemoveListItem(&(*lists)[route], CmpRoute, fwd_row));
    }

out:
    if (!add || err)
    {
        free(fwd_row);
    }

    return err;
}