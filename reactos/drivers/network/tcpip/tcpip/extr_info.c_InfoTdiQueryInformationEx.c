#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  tei_entity; int /*<<< orphan*/  tei_instance; } ;
struct TYPE_11__ {int toi_class; int /*<<< orphan*/  toi_type; TYPE_3__ toi_entity; int /*<<< orphan*/  toi_id; } ;
typedef  int /*<<< orphan*/  TDI_STATUS ;
typedef  TYPE_1__ TDIObjectID ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PUINT ;
typedef  int /*<<< orphan*/  PTDI_REQUEST ;
typedef  int /*<<< orphan*/  PNDIS_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  AT_ENTITY ; 
 int /*<<< orphan*/  CL_NL_ENTITY ; 
 int /*<<< orphan*/  CL_TL_ENTITY ; 
 int /*<<< orphan*/  CO_NL_ENTITY ; 
 int /*<<< orphan*/  CO_TL_ENTITY ; 
 int /*<<< orphan*/  DEBUG_INFO ; 
#define  ENTITY_LIST_ID 136 
#define  ENTITY_TYPE_ID 135 
 int /*<<< orphan*/  GetAddressFileInfo (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetContext (TYPE_3__) ; 
 int /*<<< orphan*/  IF_ENTITY ; 
#define  IF_MIB_STATS_ID 134 
#define  INFO_CLASS_GENERIC 133 
#define  INFO_CLASS_PROTOCOL 132 
 int /*<<< orphan*/  INFO_TYPE_ADDRESS_OBJECT ; 
 int /*<<< orphan*/  INFO_TYPE_PROVIDER ; 
#define  IP_INTFC_INFO_ID 131 
#define  IP_MIB_ADDRTABLE_ENTRY_ID 130 
#define  IP_MIB_ARPTABLE_ENTRY_ID 129 
#define  IP_SPECIFIC_MODULE_ENTRY_ID 128 
 int /*<<< orphan*/  InfoTdiQueryEntityType (TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InfoTdiQueryGetATInfo (TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InfoTdiQueryGetAddrTable (TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InfoTdiQueryGetArptableMIB (TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InfoTdiQueryGetConnectionTcpTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InfoTdiQueryGetConnectionUdpTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InfoTdiQueryGetIFInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InfoTdiQueryGetIPSnmpInfo (TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InfoTdiQueryGetInterfaceMIB (TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InfoTdiQueryGetRouteTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InfoTdiQueryListEntities (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDI_INVALID_PARAMETER ; 
 int /*<<< orphan*/  TDI_INVALID_REQUEST ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TcpUdpClassBasic ; 
 int /*<<< orphan*/  TcpUdpClassOwner ; 
 int /*<<< orphan*/  TcpUdpClassOwnerPid ; 

TDI_STATUS InfoTdiQueryInformationEx(
  PTDI_REQUEST Request,
  TDIObjectID *ID,
  PNDIS_BUFFER Buffer,
  PUINT BufferSize,
  PVOID Context)
/*
 * FUNCTION: Returns extended information
 * ARGUMENTS:
 *   Request    = Pointer to TDI request structure for the request
 *   ID         = TDI object ID
 *   Buffer     = Pointer to buffer with data to use
 *   BufferSize = Pointer to buffer with size of Buffer. On return
 *                this is filled with number of bytes returned
 *   Context    = Pointer to context buffer
 * RETURNS:
 *   Status of operation
 */
{
    PVOID EntityListContext;

    TI_DbgPrint(DEBUG_INFO,
		("InfoEx Req: %x %x %x!%04x:%d\n",
		 ID->toi_class,
		 ID->toi_type,
		 ID->toi_id,
		 ID->toi_entity.tei_entity,
		 ID->toi_entity.tei_instance));

    switch (ID->toi_class)
    {
        case INFO_CLASS_GENERIC:
           switch (ID->toi_id)
           {
              case ENTITY_LIST_ID:
                 if (ID->toi_type != INFO_TYPE_PROVIDER)
                     return TDI_INVALID_PARAMETER;

                 return InfoTdiQueryListEntities(Buffer, BufferSize);

              case ENTITY_TYPE_ID:
                 if (ID->toi_type != INFO_TYPE_PROVIDER)
                     return TDI_INVALID_PARAMETER;

                 return InfoTdiQueryEntityType(ID->toi_entity, Buffer, BufferSize);

              default:
                 return TDI_INVALID_REQUEST;
           }

        case INFO_CLASS_PROTOCOL:
           if (ID->toi_type == INFO_TYPE_ADDRESS_OBJECT)
           {
               if ((EntityListContext = GetContext(ID->toi_entity)))
                    return GetAddressFileInfo(ID, EntityListContext, Buffer, BufferSize);
               else
                    return TDI_INVALID_PARAMETER;
           }

           switch (ID->toi_id)
           {
              case IF_MIB_STATS_ID:
                 if (ID->toi_type != INFO_TYPE_PROVIDER)
                     return TDI_INVALID_PARAMETER;

                 if (ID->toi_entity.tei_entity == IF_ENTITY)
                     if ((EntityListContext = GetContext(ID->toi_entity)))
                         return InfoTdiQueryGetInterfaceMIB(ID->toi_entity, EntityListContext, Buffer, BufferSize);
                     else
                         return TDI_INVALID_PARAMETER;
                 else if (ID->toi_entity.tei_entity == CL_NL_ENTITY ||
                          ID->toi_entity.tei_entity == CO_NL_ENTITY)
                     if ((EntityListContext = GetContext(ID->toi_entity)))
                         return InfoTdiQueryGetIPSnmpInfo(ID->toi_entity, EntityListContext, Buffer, BufferSize);
                     else
                         return TDI_INVALID_PARAMETER;
                 else if (ID->toi_entity.tei_entity == AT_ENTITY)
                     if ((EntityListContext = GetContext(ID->toi_entity)))
                         return InfoTdiQueryGetATInfo(ID->toi_entity, EntityListContext, Buffer, BufferSize);
                     else
                         return TDI_INVALID_PARAMETER;
                 else
                     return TDI_INVALID_PARAMETER;

              case IP_MIB_ADDRTABLE_ENTRY_ID:
                 if (ID->toi_type != INFO_TYPE_PROVIDER)
                     return TDI_INVALID_PARAMETER;

                 if (ID->toi_entity.tei_entity == CL_NL_ENTITY ||
                     ID->toi_entity.tei_entity == CO_NL_ENTITY)
                    return InfoTdiQueryGetAddrTable(ID->toi_entity, Buffer, BufferSize);
                else if (ID->toi_entity.tei_entity == CO_TL_ENTITY)
                     if ((EntityListContext = GetContext(ID->toi_entity)))
                         return InfoTdiQueryGetConnectionTcpTable(EntityListContext, Buffer, BufferSize, TcpUdpClassOwnerPid);
                     else
                         return TDI_INVALID_PARAMETER;
                else if (ID->toi_entity.tei_entity == CL_TL_ENTITY)
                     if ((EntityListContext = GetContext(ID->toi_entity)))
                         return InfoTdiQueryGetConnectionUdpTable(EntityListContext, Buffer, BufferSize, TcpUdpClassOwnerPid);
                     else
                         return TDI_INVALID_PARAMETER;
                else
                    return TDI_INVALID_PARAMETER;

              case IP_MIB_ARPTABLE_ENTRY_ID:
                 if (ID->toi_type != INFO_TYPE_PROVIDER)
                     return TDI_INVALID_PARAMETER;

                 if (ID->toi_entity.tei_entity == AT_ENTITY)
                     if ((EntityListContext = GetContext(ID->toi_entity)))
                         return InfoTdiQueryGetArptableMIB(ID->toi_entity, EntityListContext,
                                                           Buffer, BufferSize);
                     else
                         return TDI_INVALID_PARAMETER;
                 else if (ID->toi_entity.tei_entity == CO_NL_ENTITY ||
                          ID->toi_entity.tei_entity == CL_NL_ENTITY)
                     if ((EntityListContext = GetContext(ID->toi_entity)))
                         return InfoTdiQueryGetRouteTable(EntityListContext, Buffer, BufferSize);
                     else
                         return TDI_INVALID_PARAMETER;
                 else if (ID->toi_entity.tei_entity == CO_TL_ENTITY)
                     if ((EntityListContext = GetContext(ID->toi_entity)))
                         return InfoTdiQueryGetConnectionTcpTable(EntityListContext, Buffer, BufferSize, TcpUdpClassBasic);
                     else
                         return TDI_INVALID_PARAMETER;
                 else if (ID->toi_entity.tei_entity == CL_TL_ENTITY)
                     if ((EntityListContext = GetContext(ID->toi_entity)))
                         return InfoTdiQueryGetConnectionUdpTable(EntityListContext, Buffer, BufferSize, TcpUdpClassBasic);
                     else
                         return TDI_INVALID_PARAMETER;
                 else
                     return TDI_INVALID_PARAMETER;

              case IP_SPECIFIC_MODULE_ENTRY_ID:
                 if (ID->toi_type != INFO_TYPE_PROVIDER)
                     return TDI_INVALID_PARAMETER;

                 if (ID->toi_entity.tei_entity == CO_TL_ENTITY)
                     if ((EntityListContext = GetContext(ID->toi_entity)))
                         return InfoTdiQueryGetConnectionTcpTable(EntityListContext, Buffer, BufferSize, TcpUdpClassOwner);
                     else
                         return TDI_INVALID_PARAMETER;
                 else if (ID->toi_entity.tei_entity == CL_TL_ENTITY)
                     if ((EntityListContext = GetContext(ID->toi_entity)))
                         return InfoTdiQueryGetConnectionUdpTable(EntityListContext, Buffer, BufferSize, TcpUdpClassOwner);
                     else
                         return TDI_INVALID_PARAMETER;
                 else
                     return TDI_INVALID_PARAMETER;

#if 0
              case IP_INTFC_INFO_ID:
                 if (ID->toi_type != INFO_TYPE_PROVIDER)
                     return TDI_INVALID_PARAMETER;

                 return InfoTdiQueryGetIFInfo(Context, Buffer, BufferSize);
#endif

              default:
                 return TDI_INVALID_REQUEST;
           }

        default:
           return TDI_INVALID_REQUEST;
    }
}