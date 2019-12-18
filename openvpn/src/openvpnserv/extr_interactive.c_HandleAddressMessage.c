#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * undo_lists_t ;
struct TYPE_15__ {int index; int /*<<< orphan*/  name; } ;
struct TYPE_14__ {scalar_t__ type; } ;
struct TYPE_16__ {TYPE_2__ iface; scalar_t__ prefix_len; int /*<<< orphan*/  address; int /*<<< orphan*/  family; TYPE_1__ header; } ;
typedef  TYPE_3__ address_message_t ;
typedef  scalar_t__ UINT8 ;
struct TYPE_17__ {int InterfaceIndex; int /*<<< orphan*/  InterfaceLuid; scalar_t__ OnLinkPrefixLength; int /*<<< orphan*/  Address; } ;
typedef  TYPE_4__* PMIB_UNICASTIPADDRESS_ROW ;
typedef  int /*<<< orphan*/  NET_LUID ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ AddListItem (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  CmpAddress ; 
 scalar_t__ CreateUnicastIpAddressEntry (TYPE_4__*) ; 
 scalar_t__ DeleteAddress (TYPE_4__*) ; 
 scalar_t__ ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  InitializeUnicastIpAddressEntry (TYPE_4__*) ; 
 scalar_t__ InterfaceLuid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* RemoveListItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 size_t address ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 TYPE_4__* malloc (int) ; 
 scalar_t__ msg_add_address ; 
 int /*<<< orphan*/  sockaddr_inet (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static DWORD
HandleAddressMessage(address_message_t *msg, undo_lists_t *lists)
{
    DWORD err;
    PMIB_UNICASTIPADDRESS_ROW addr_row;
    BOOL add = msg->header.type == msg_add_address;

    addr_row = malloc(sizeof(*addr_row));
    if (addr_row == NULL)
    {
        return ERROR_OUTOFMEMORY;
    }

    InitializeUnicastIpAddressEntry(addr_row);
    addr_row->Address = sockaddr_inet(msg->family, &msg->address);
    addr_row->OnLinkPrefixLength = (UINT8) msg->prefix_len;

    if (msg->iface.index != -1)
    {
        addr_row->InterfaceIndex = msg->iface.index;
    }
    else
    {
        NET_LUID luid;
        err = InterfaceLuid(msg->iface.name, &luid);
        if (err)
        {
            goto out;
        }
        addr_row->InterfaceLuid = luid;
    }

    if (add)
    {
        err = CreateUnicastIpAddressEntry(addr_row);
        if (err)
        {
            goto out;
        }

        err = AddListItem(&(*lists)[address], addr_row);
        if (err)
        {
            DeleteAddress(addr_row);
        }
    }
    else
    {
        err = DeleteAddress(addr_row);
        if (err)
        {
            goto out;
        }

        free(RemoveListItem(&(*lists)[address], CmpAddress, addr_row));
    }

out:
    if (!add || err)
    {
        free(addr_row);
    }

    return err;
}