#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT64 ;
typedef  scalar_t__ UINT32 ;
struct TYPE_19__ {int /*<<< orphan*/  AccessLength; int /*<<< orphan*/  Length; int /*<<< orphan*/  Connection; } ;
struct TYPE_17__ {scalar_t__ (* Setup ) (TYPE_5__*,int /*<<< orphan*/ ,TYPE_6__*,void**) ;scalar_t__ (* Handler ) (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,TYPE_6__*,void*) ;int HandlerFlags; TYPE_6__* Context; } ;
struct TYPE_16__ {scalar_t__ SpaceId; int Flags; TYPE_5__* Handler; scalar_t__ Address; int /*<<< orphan*/  Node; } ;
struct TYPE_15__ {void* RegionContext; } ;
struct TYPE_14__ {scalar_t__ BitLength; scalar_t__ PinNumberIndex; int /*<<< orphan*/  AccessLength; int /*<<< orphan*/  ResourceLength; int /*<<< orphan*/  ResourceBuffer; } ;
struct TYPE_18__ {TYPE_4__ AddressSpace; TYPE_3__ Region; TYPE_2__ Extra; TYPE_1__ Field; } ;
typedef  scalar_t__ ACPI_STATUS ;
typedef  scalar_t__ ACPI_PHYSICAL_ADDRESS ;
typedef  TYPE_5__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_6__ ACPI_CONNECTION_INFO ;
typedef  scalar_t__ (* ACPI_ADR_SPACE_SETUP ) (TYPE_5__*,int /*<<< orphan*/ ,TYPE_6__*,void**) ;
typedef  scalar_t__ (* ACPI_ADR_SPACE_HANDLER ) (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,TYPE_6__*,void*) ;

/* Variables and functions */
 int ACPI_ADDR_HANDLER_DEFAULT_INSTALLED ; 
 scalar_t__ ACPI_ADR_SPACE_EC ; 
 scalar_t__ ACPI_ADR_SPACE_GPIO ; 
 scalar_t__ ACPI_ADR_SPACE_GSBUS ; 
 int /*<<< orphan*/  ACPI_DB_OPREGION ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_REGION_ACTIVATE ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AE_NOT_EXIST ; 
 scalar_t__ AE_TIME ; 
 int AOPOBJ_SETUP_COMPLETE ; 
 int /*<<< orphan*/  AcpiExEnterInterpreter () ; 
 int /*<<< orphan*/  AcpiExExitInterpreter () ; 
 TYPE_5__* AcpiNsGetSecondaryObject (TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiUtGetNodeName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtGetRegionName (scalar_t__) ; 
 int /*<<< orphan*/  EvAddressSpaceDispatch ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 

ACPI_STATUS
AcpiEvAddressSpaceDispatch (
    ACPI_OPERAND_OBJECT     *RegionObj,
    ACPI_OPERAND_OBJECT     *FieldObj,
    UINT32                  Function,
    UINT32                  RegionOffset,
    UINT32                  BitWidth,
    UINT64                  *Value)
{
    ACPI_STATUS             Status;
    ACPI_ADR_SPACE_HANDLER  Handler;
    ACPI_ADR_SPACE_SETUP    RegionSetup;
    ACPI_OPERAND_OBJECT     *HandlerDesc;
    ACPI_OPERAND_OBJECT     *RegionObj2;
    void                    *RegionContext = NULL;
    ACPI_CONNECTION_INFO    *Context;
    ACPI_PHYSICAL_ADDRESS   Address;


    ACPI_FUNCTION_TRACE (EvAddressSpaceDispatch);


    RegionObj2 = AcpiNsGetSecondaryObject (RegionObj);
    if (!RegionObj2)
    {
        return_ACPI_STATUS (AE_NOT_EXIST);
    }

    /* Ensure that there is a handler associated with this region */

    HandlerDesc = RegionObj->Region.Handler;
    if (!HandlerDesc)
    {
        ACPI_ERROR ((AE_INFO,
            "No handler for Region [%4.4s] (%p) [%s]",
            AcpiUtGetNodeName (RegionObj->Region.Node),
            RegionObj, AcpiUtGetRegionName (RegionObj->Region.SpaceId)));

        return_ACPI_STATUS (AE_NOT_EXIST);
    }

    Context = HandlerDesc->AddressSpace.Context;

    /*
     * It may be the case that the region has never been initialized.
     * Some types of regions require special init code
     */
    if (!(RegionObj->Region.Flags & AOPOBJ_SETUP_COMPLETE))
    {
        /* This region has not been initialized yet, do it */

        RegionSetup = HandlerDesc->AddressSpace.Setup;
        if (!RegionSetup)
        {
            /* No initialization routine, exit with error */

            ACPI_ERROR ((AE_INFO,
                "No init routine for region(%p) [%s]",
                RegionObj, AcpiUtGetRegionName (RegionObj->Region.SpaceId)));
            return_ACPI_STATUS (AE_NOT_EXIST);
        }

        /*
         * We must exit the interpreter because the region setup will
         * potentially execute control methods (for example, the _REG method
         * for this region)
         */
        AcpiExExitInterpreter ();

        Status = RegionSetup (RegionObj, ACPI_REGION_ACTIVATE,
            Context, &RegionContext);

        /* Re-enter the interpreter */

        AcpiExEnterInterpreter ();

        /* Check for failure of the Region Setup */

        if (ACPI_FAILURE (Status))
        {
            ACPI_EXCEPTION ((AE_INFO, Status,
                "During region initialization: [%s]",
                AcpiUtGetRegionName (RegionObj->Region.SpaceId)));
            return_ACPI_STATUS (Status);
        }

        /* Region initialization may have been completed by RegionSetup */

        if (!(RegionObj->Region.Flags & AOPOBJ_SETUP_COMPLETE))
        {
            RegionObj->Region.Flags |= AOPOBJ_SETUP_COMPLETE;

            /*
             * Save the returned context for use in all accesses to
             * the handler for this particular region
             */
            if (!(RegionObj2->Extra.RegionContext))
            {
                RegionObj2->Extra.RegionContext = RegionContext;
            }
        }
    }

    /* We have everything we need, we can invoke the address space handler */

    Handler = HandlerDesc->AddressSpace.Handler;
    Address = (RegionObj->Region.Address + RegionOffset);

    /*
     * Special handling for GenericSerialBus and GeneralPurposeIo:
     * There are three extra parameters that must be passed to the
     * handler via the context:
     *   1) Connection buffer, a resource template from Connection() op
     *   2) Length of the above buffer
     *   3) Actual access length from the AccessAs() op
     *
     * In addition, for GeneralPurposeIo, the Address and BitWidth fields
     * are defined as follows:
     *   1) Address is the pin number index of the field (bit offset from
     *      the previous Connection)
     *   2) BitWidth is the actual bit length of the field (number of pins)
     */
    if ((RegionObj->Region.SpaceId == ACPI_ADR_SPACE_GSBUS) &&
        Context &&
        FieldObj)
    {
        /* Get the Connection (ResourceTemplate) buffer */

        Context->Connection = FieldObj->Field.ResourceBuffer;
        Context->Length = FieldObj->Field.ResourceLength;
        Context->AccessLength = FieldObj->Field.AccessLength;
    }
    if ((RegionObj->Region.SpaceId == ACPI_ADR_SPACE_GPIO) &&
        Context &&
        FieldObj)
    {
        /* Get the Connection (ResourceTemplate) buffer */

        Context->Connection = FieldObj->Field.ResourceBuffer;
        Context->Length = FieldObj->Field.ResourceLength;
        Context->AccessLength = FieldObj->Field.AccessLength;
        Address = FieldObj->Field.PinNumberIndex;
        BitWidth = FieldObj->Field.BitLength;
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_OPREGION,
        "Handler %p (@%p) Address %8.8X%8.8X [%s]\n",
        &RegionObj->Region.Handler->AddressSpace, Handler,
        ACPI_FORMAT_UINT64 (Address),
        AcpiUtGetRegionName (RegionObj->Region.SpaceId)));

    if (!(HandlerDesc->AddressSpace.HandlerFlags &
        ACPI_ADDR_HANDLER_DEFAULT_INSTALLED))
    {
        /*
         * For handlers other than the default (supplied) handlers, we must
         * exit the interpreter because the handler *might* block -- we don't
         * know what it will do, so we can't hold the lock on the interpreter.
         */
        AcpiExExitInterpreter();
    }

    /* Call the handler */

    Status = Handler (Function, Address, BitWidth, Value, Context,
        RegionObj2->Extra.RegionContext);

    if (ACPI_FAILURE (Status))
    {
        ACPI_EXCEPTION ((AE_INFO, Status, "Returned by Handler for [%s]",
            AcpiUtGetRegionName (RegionObj->Region.SpaceId)));

        /*
         * Special case for an EC timeout. These are seen so frequently
         * that an additional error message is helpful
         */
        if ((RegionObj->Region.SpaceId == ACPI_ADR_SPACE_EC) &&
            (Status == AE_TIME))
        {
            ACPI_ERROR ((AE_INFO,
                "Timeout from EC hardware or EC device driver"));
        }
    }

    if (!(HandlerDesc->AddressSpace.HandlerFlags &
        ACPI_ADDR_HANDLER_DEFAULT_INSTALLED))
    {
        /*
         * We just returned from a non-default handler, we must re-enter the
         * interpreter
         */
        AcpiExEnterInterpreter ();
    }

    return_ACPI_STATUS (Status);
}