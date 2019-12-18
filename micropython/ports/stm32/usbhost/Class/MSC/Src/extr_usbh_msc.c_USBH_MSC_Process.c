#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
typedef  void* USBH_StatusTypeDef ;
struct TYPE_18__ {int /*<<< orphan*/  (* pUser ) (TYPE_3__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  os_event; int /*<<< orphan*/  Timer; TYPE_1__* pActiveClass; } ;
typedef  TYPE_3__ USBH_HandleTypeDef ;
struct TYPE_20__ {int /*<<< orphan*/  ascq; int /*<<< orphan*/  asc; int /*<<< orphan*/  key; } ;
struct TYPE_19__ {int state; size_t current_lun; size_t max_lun; TYPE_2__* unit; int /*<<< orphan*/  timer; } ;
struct TYPE_14__ {int block_nbr; int block_size; } ;
struct TYPE_15__ {int /*<<< orphan*/  revision_id; int /*<<< orphan*/  product_id; int /*<<< orphan*/  vendor_id; } ;
struct TYPE_17__ {int state; void* prev_ready_state; int state_changed; void* error; TYPE_8__ sense; TYPE_10__ capacity; TYPE_12__ inquiry; } ;
struct TYPE_16__ {TYPE_4__* pData; } ;
typedef  TYPE_4__ MSC_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_USER_CLASS_ACTIVE ; 
 void* MSC_ERROR ; 
#define  MSC_IDLE 134 
#define  MSC_INIT 133 
 void* MSC_NOT_READY ; 
 void* MSC_OK ; 
#define  MSC_READ_CAPACITY10 132 
#define  MSC_READ_INQUIRY 131 
#define  MSC_REQUEST_SENSE 130 
#define  MSC_TEST_UNIT_READY 129 
#define  MSC_UNRECOVERED_ERROR 128 
 int /*<<< orphan*/  SCSI_SENSE_KEY_NOT_READY ; 
 int /*<<< orphan*/  SCSI_SENSE_KEY_UNIT_ATTENTION ; 
 void* USBH_BUSY ; 
 int /*<<< orphan*/  USBH_CLASS_EVENT ; 
 void* USBH_FAIL ; 
 void* USBH_MSC_SCSI_Inquiry (TYPE_3__*,size_t,TYPE_12__*) ; 
 void* USBH_MSC_SCSI_ReadCapacity (TYPE_3__*,size_t,TYPE_10__*) ; 
 void* USBH_MSC_SCSI_RequestSense (TYPE_3__*,size_t,TYPE_8__*) ; 
 void* USBH_MSC_SCSI_TestUnitReady (TYPE_3__*,size_t) ; 
 void* USBH_OK ; 
 void* USBH_UNRECOVERED_ERROR ; 
 int /*<<< orphan*/  USBH_UsrLog (char*,...) ; 
 int /*<<< orphan*/  osMessagePut (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_MSC_Process(USBH_HandleTypeDef *phost)
{
  MSC_HandleTypeDef *MSC_Handle =  phost->pActiveClass->pData;
  USBH_StatusTypeDef error = USBH_BUSY ;
  USBH_StatusTypeDef scsi_status = USBH_BUSY ;  
  USBH_StatusTypeDef ready_status = USBH_BUSY ;
  
  switch (MSC_Handle->state)
  {
  case MSC_INIT:
    
    if(MSC_Handle->current_lun < MSC_Handle->max_lun)
    {

      MSC_Handle->unit[MSC_Handle->current_lun].error = MSC_NOT_READY;
      /* Switch MSC REQ state machine */
      switch (MSC_Handle->unit[MSC_Handle->current_lun].state)
      {
      case MSC_INIT:
        USBH_UsrLog ("LUN #%d: ", MSC_Handle->current_lun);
        MSC_Handle->unit[MSC_Handle->current_lun].state = MSC_READ_INQUIRY;
        MSC_Handle->timer = phost->Timer + 10000;
        
      case MSC_READ_INQUIRY:
        scsi_status = USBH_MSC_SCSI_Inquiry(phost, MSC_Handle->current_lun, &MSC_Handle->unit[MSC_Handle->current_lun].inquiry);
        
        if( scsi_status == USBH_OK)
        {
          USBH_UsrLog ("Inquiry Vendor  : %s", MSC_Handle->unit[MSC_Handle->current_lun].inquiry.vendor_id);
          USBH_UsrLog ("Inquiry Product : %s", MSC_Handle->unit[MSC_Handle->current_lun].inquiry.product_id);
          USBH_UsrLog ("Inquiry Version : %s", MSC_Handle->unit[MSC_Handle->current_lun].inquiry.revision_id);
          MSC_Handle->unit[MSC_Handle->current_lun].state = MSC_TEST_UNIT_READY;        
        }
        if( scsi_status == USBH_FAIL)
        {
          MSC_Handle->unit[MSC_Handle->current_lun].state = MSC_REQUEST_SENSE;         
        }
        else if(scsi_status == USBH_UNRECOVERED_ERROR)
        {
          MSC_Handle->unit[MSC_Handle->current_lun].state = MSC_IDLE;
          MSC_Handle->unit[MSC_Handle->current_lun].error = MSC_ERROR;
        }
        break;    
        
      case MSC_TEST_UNIT_READY:
        ready_status = USBH_MSC_SCSI_TestUnitReady(phost, MSC_Handle->current_lun);
        
        if( ready_status == USBH_OK)
        {
          if( MSC_Handle->unit[MSC_Handle->current_lun].prev_ready_state != USBH_OK)
          {
            MSC_Handle->unit[MSC_Handle->current_lun].state_changed = 1;
            USBH_UsrLog ("Mass Storage Device ready");
          }
          else
          {
            MSC_Handle->unit[MSC_Handle->current_lun].state_changed = 0;
          }
          MSC_Handle->unit[MSC_Handle->current_lun].state = MSC_READ_CAPACITY10;
          MSC_Handle->unit[MSC_Handle->current_lun].error = MSC_OK;
          MSC_Handle->unit[MSC_Handle->current_lun].prev_ready_state = USBH_OK;
        }
        if( ready_status == USBH_FAIL)
        {
          /* Media not ready, so try to check again during 10s */
          if( MSC_Handle->unit[MSC_Handle->current_lun].prev_ready_state != USBH_FAIL)
          {
            MSC_Handle->unit[MSC_Handle->current_lun].state_changed = 1;
            USBH_UsrLog ("Mass Storage Device NOT ready");
          }
          else
          {
            MSC_Handle->unit[MSC_Handle->current_lun].state_changed = 0;
          }         
            MSC_Handle->unit[MSC_Handle->current_lun].state = MSC_REQUEST_SENSE; 
            MSC_Handle->unit[MSC_Handle->current_lun].error = MSC_NOT_READY;
            MSC_Handle->unit[MSC_Handle->current_lun].prev_ready_state = USBH_FAIL;
        }
        else if(ready_status == USBH_UNRECOVERED_ERROR)
        {
          MSC_Handle->unit[MSC_Handle->current_lun].state = MSC_IDLE;
          MSC_Handle->unit[MSC_Handle->current_lun].error = MSC_ERROR;
        }
        break;
        
      case MSC_READ_CAPACITY10:   
        scsi_status = USBH_MSC_SCSI_ReadCapacity(phost,MSC_Handle->current_lun, &MSC_Handle->unit[MSC_Handle->current_lun].capacity) ;
        
        if(scsi_status == USBH_OK)
        {
          if(MSC_Handle->unit[MSC_Handle->current_lun].state_changed == 1)
          {
            USBH_UsrLog ("Mass Storage Device capacity : %lu MB", \
              (int32_t)((MSC_Handle->unit[MSC_Handle->current_lun].capacity.block_nbr * MSC_Handle->unit[MSC_Handle->current_lun].capacity.block_size)/1024/1024));
            USBH_UsrLog ("Block number : %lu", (int32_t)(MSC_Handle->unit[MSC_Handle->current_lun].capacity.block_nbr));
            USBH_UsrLog ("Block Size   : %lu", (int32_t)(MSC_Handle->unit[MSC_Handle->current_lun].capacity.block_size));
          }
          MSC_Handle->unit[MSC_Handle->current_lun].state = MSC_IDLE;
          MSC_Handle->unit[MSC_Handle->current_lun].error = MSC_OK;
          MSC_Handle->current_lun++;
        }
        else if( scsi_status == USBH_FAIL)
        {
          MSC_Handle->unit[MSC_Handle->current_lun].state = MSC_REQUEST_SENSE;
        }
        else if(scsi_status == USBH_UNRECOVERED_ERROR)
        {
          MSC_Handle->unit[MSC_Handle->current_lun].state = MSC_IDLE;
          MSC_Handle->unit[MSC_Handle->current_lun].error = MSC_ERROR;
        }
        break;
        
      case MSC_REQUEST_SENSE:
        scsi_status = USBH_MSC_SCSI_RequestSense(phost,  MSC_Handle->current_lun, &MSC_Handle->unit[MSC_Handle->current_lun].sense);
        
        if( scsi_status == USBH_OK)
        {
          if((MSC_Handle->unit[MSC_Handle->current_lun].sense.key == SCSI_SENSE_KEY_UNIT_ATTENTION) ||
             (MSC_Handle->unit[MSC_Handle->current_lun].sense.key == SCSI_SENSE_KEY_NOT_READY) )   
          {
            
            if(phost->Timer <= MSC_Handle->timer)
            {
              MSC_Handle->unit[MSC_Handle->current_lun].state = MSC_TEST_UNIT_READY;
              break;
            }        
          }
          
          USBH_UsrLog ("Sense Key  : %x", MSC_Handle->unit[MSC_Handle->current_lun].sense.key);
          USBH_UsrLog ("Additional Sense Code : %x", MSC_Handle->unit[MSC_Handle->current_lun].sense.asc);
          USBH_UsrLog ("Additional Sense Code Qualifier: %x", MSC_Handle->unit[MSC_Handle->current_lun].sense.ascq);
          MSC_Handle->unit[MSC_Handle->current_lun].state = MSC_IDLE;
          MSC_Handle->current_lun++;
        }
        if( scsi_status == USBH_FAIL)
        {
          USBH_UsrLog ("Mass Storage Device NOT ready");
          MSC_Handle->unit[MSC_Handle->current_lun].state = MSC_UNRECOVERED_ERROR; 
        }
        else if(scsi_status == USBH_UNRECOVERED_ERROR)
        {
          MSC_Handle->unit[MSC_Handle->current_lun].state = MSC_IDLE;
          MSC_Handle->unit[MSC_Handle->current_lun].error = MSC_ERROR;   
        }
        break;  
    
      case MSC_UNRECOVERED_ERROR: 
        MSC_Handle->current_lun++;
        break;  
        
      default:
        break;
      }
      
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_CLASS_EVENT, 0);
#endif       
    }
    else
    {
      MSC_Handle->current_lun = 0;
    MSC_Handle->state = MSC_IDLE;
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_CLASS_EVENT, 0);
#endif 
    phost->pUser(phost, HOST_USER_CLASS_ACTIVE);     
    }
    break;

  case MSC_IDLE:
    error = USBH_OK;  
    break;
    
  default:
    break; 
  }
  return error;
}