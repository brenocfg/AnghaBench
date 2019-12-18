#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {int /*<<< orphan*/  tei_entity; } ;
struct TYPE_8__ {int /*<<< orphan*/  Connection; } ;
struct TYPE_7__ {int toi_class; int const toi_type; TYPE_6__ toi_entity; int /*<<< orphan*/  toi_id; } ;
typedef  int /*<<< orphan*/  TDI_STATUS ;
typedef  TYPE_1__ TDIObjectID ;
typedef  void* PVOID ;
typedef  int /*<<< orphan*/  PTDI_REQUEST ;
typedef  TYPE_2__* PADDRESS_FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AT_ENTITY ; 
 int /*<<< orphan*/  CL_NL_ENTITY ; 
 int /*<<< orphan*/  CO_NL_ENTITY ; 
 int /*<<< orphan*/  DbgPrint (char*,int) ; 
 void* GetContext (TYPE_6__) ; 
#define  INFO_CLASS_PROTOCOL 132 
#define  INFO_TYPE_ADDRESS_OBJECT 131 
#define  INFO_TYPE_CONNECTION 130 
#define  INFO_TYPE_PROVIDER 129 
#define  IP_MIB_ARPTABLE_ENTRY_ID 128 
 int /*<<< orphan*/  InfoTdiSetArptableMIB (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InfoTdiSetRoute (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetAddressFileInfo (TYPE_1__*,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetConnectionInfo (TYPE_1__*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDI_INVALID_PARAMETER ; 
 int /*<<< orphan*/  TDI_INVALID_REQUEST ; 

TDI_STATUS InfoTdiSetInformationEx
(PTDI_REQUEST Request,
 TDIObjectID *ID,
 PVOID Buffer,
 UINT BufferSize)
/*
 * FUNCTION: Sets extended information
 * ARGUMENTS:
 *   Request    = Pointer to TDI request structure for the request
 *   ID         = Pointer to TDI object ID
 *   Buffer     = Pointer to buffer with data to use
 *   BufferSize = Size of Buffer
 * RETURNS:
 *   Status of operation
 */
{
    PVOID EntityListContext;

    switch (ID->toi_class)
    {
        case INFO_CLASS_PROTOCOL:
        {
            switch (ID->toi_type)
            {
                case INFO_TYPE_ADDRESS_OBJECT:
                {
                    if ((EntityListContext = GetContext(ID->toi_entity)))
                        return SetAddressFileInfo(ID, EntityListContext, Buffer, BufferSize);
                    else
                        return TDI_INVALID_PARAMETER;
                }
                case INFO_TYPE_CONNECTION:
                {
                    PADDRESS_FILE AddressFile = GetContext(ID->toi_entity);
                    if (AddressFile == NULL)
                        return TDI_INVALID_PARAMETER;
                    return SetConnectionInfo(ID, AddressFile->Connection, Buffer, BufferSize);
                }
                case INFO_TYPE_PROVIDER:
                {
                    switch (ID->toi_id)
                    {
                        case IP_MIB_ARPTABLE_ENTRY_ID:
                            if (ID->toi_type != INFO_TYPE_PROVIDER)
                                return TDI_INVALID_PARAMETER;

                            if (ID->toi_entity.tei_entity == AT_ENTITY)
                                if ((EntityListContext = GetContext(ID->toi_entity)))
                                    return InfoTdiSetArptableMIB(EntityListContext, Buffer,
                                        BufferSize);
                                else
                                    return TDI_INVALID_PARAMETER;
                            else if (ID->toi_entity.tei_entity == CL_NL_ENTITY
                                || ID->toi_entity.tei_entity == CO_NL_ENTITY)
                                if ((EntityListContext = GetContext(ID->toi_entity)))
                                    return InfoTdiSetRoute(EntityListContext, Buffer, BufferSize);
                                else
                                    return TDI_INVALID_PARAMETER;
                            else
                                return TDI_INVALID_PARAMETER;

                        default:
                            return TDI_INVALID_REQUEST;
                    }
                }
                default:
                    DbgPrint("TCPIP: IOCTL_TCP_SET_INFORMATION_EX - Unrecognized information type for INFO_CLASS_PROTOCOL: %#x.\n", ID->toi_type);
                    return TDI_INVALID_PARAMETER;
            }
            break;
        }
        default:
            DbgPrint("TCPIP: IOCTL_TCP_SET_INFORMATION_EX - Unrecognized information class %#x.\n", ID->toi_class);
            return TDI_INVALID_REQUEST;
    }
}