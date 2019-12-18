#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * undo_lists_t ;
struct TYPE_12__ {int /*<<< orphan*/  index; } ;
struct TYPE_11__ {scalar_t__ type; } ;
struct TYPE_13__ {TYPE_2__ iface; TYPE_1__ header; } ;
typedef  TYPE_3__ block_dns_message_t ;
struct TYPE_14__ {scalar_t__ metric_v4; scalar_t__ metric_v6; int /*<<< orphan*/ * engine; int /*<<< orphan*/  index; } ;
typedef  TYPE_4__ block_dns_data_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_15__ {int /*<<< orphan*/ * exe_path; } ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ AddListItem (int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ BLOCK_DNS_IFACE_METRIC ; 
 int /*<<< orphan*/  BlockDNSErrHandler ; 
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  CmpEngine ; 
 scalar_t__ ERROR_OUTOFMEMORY ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  MsgToEventLog (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 TYPE_4__* RemoveListItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 scalar_t__ add_block_dns_filters (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t block_dns ; 
 scalar_t__ delete_block_dns_filters (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 void* get_interface_metric (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 TYPE_4__* malloc (int) ; 
 scalar_t__ msg_add_block_dns ; 
 scalar_t__ set_interface_metric (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_5__ settings ; 

__attribute__((used)) static DWORD
HandleBlockDNSMessage(const block_dns_message_t *msg, undo_lists_t *lists)
{
    DWORD err = 0;
    block_dns_data_t *interface_data;
    HANDLE engine = NULL;
    LPCWSTR exe_path;

#ifdef UNICODE
    exe_path = settings.exe_path;
#else
    WCHAR wide_path[MAX_PATH];
    MultiByteToWideChar(CP_UTF8, 0, settings.exe_path, MAX_PATH, wide_path, MAX_PATH);
    exe_path = wide_path;
#endif

    if (msg->header.type == msg_add_block_dns)
    {
        err = add_block_dns_filters(&engine, msg->iface.index, exe_path, BlockDNSErrHandler);
        if (!err)
        {
            interface_data = malloc(sizeof(block_dns_data_t));
            if (!interface_data)
            {
                return ERROR_OUTOFMEMORY;
            }
            interface_data->engine = engine;
            interface_data->index = msg->iface.index;
            int is_auto = 0;
            interface_data->metric_v4 = get_interface_metric(msg->iface.index,
                                                             AF_INET, &is_auto);
            if (is_auto)
            {
                interface_data->metric_v4 = 0;
            }
            interface_data->metric_v6 = get_interface_metric(msg->iface.index,
                                                             AF_INET6, &is_auto);
            if (is_auto)
            {
                interface_data->metric_v6 = 0;
            }
            err = AddListItem(&(*lists)[block_dns], interface_data);
            if (!err)
            {
                err = set_interface_metric(msg->iface.index, AF_INET,
                                           BLOCK_DNS_IFACE_METRIC);
                if (!err)
                {
                    set_interface_metric(msg->iface.index, AF_INET6,
                                         BLOCK_DNS_IFACE_METRIC);
                }
            }
        }
    }
    else
    {
        interface_data = RemoveListItem(&(*lists)[block_dns], CmpEngine, NULL);
        if (interface_data)
        {
            engine = interface_data->engine;
            err = delete_block_dns_filters(engine);
            engine = NULL;
            if (interface_data->metric_v4 >= 0)
            {
                set_interface_metric(msg->iface.index, AF_INET,
                                     interface_data->metric_v4);
            }
            if (interface_data->metric_v6 >= 0)
            {
                set_interface_metric(msg->iface.index, AF_INET6,
                                     interface_data->metric_v6);
            }
            free(interface_data);
        }
        else
        {
            MsgToEventLog(M_ERR, TEXT("No previous block DNS filters to delete"));
        }
    }

    if (err && engine)
    {
        delete_block_dns_filters(engine);
    }

    return err;
}