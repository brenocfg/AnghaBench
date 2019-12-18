#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  USBH_URBStateTypeDef ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_12__ {int /*<<< orphan*/  w; } ;
struct TYPE_13__ {int bmRequestType; TYPE_1__ wLength; } ;
struct TYPE_14__ {TYPE_2__ b; scalar_t__ d8; } ;
struct TYPE_15__ {int state; int /*<<< orphan*/  errorcount; int /*<<< orphan*/  pipe_out; int /*<<< orphan*/  timer; int /*<<< orphan*/  pipe_in; int /*<<< orphan*/  length; int /*<<< orphan*/  buff; TYPE_3__ setup; } ;
struct TYPE_16__ {TYPE_4__ Control; int /*<<< orphan*/  RequestState; int /*<<< orphan*/  os_event; int /*<<< orphan*/  Timer; } ;
typedef  TYPE_5__ USBH_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SEND ; 
 void* CTRL_COMPLETE ; 
#define  CTRL_DATA_IN 138 
#define  CTRL_DATA_IN_WAIT 137 
#define  CTRL_DATA_OUT 136 
#define  CTRL_DATA_OUT_WAIT 135 
#define  CTRL_ERROR 134 
#define  CTRL_SETUP 133 
#define  CTRL_SETUP_WAIT 132 
 int CTRL_STALLED ; 
#define  CTRL_STATUS_IN 131 
#define  CTRL_STATUS_IN_WAIT 130 
#define  CTRL_STATUS_OUT 129 
#define  CTRL_STATUS_OUT_WAIT 128 
 int /*<<< orphan*/  USBH_BUSY ; 
 int /*<<< orphan*/  USBH_CONTROL_EVENT ; 
 int /*<<< orphan*/  USBH_CtlReceiveData (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_CtlSendData (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USBH_CtlSendSetup (TYPE_5__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_ErrLog (char*) ; 
 int /*<<< orphan*/  USBH_FAIL ; 
 int /*<<< orphan*/  USBH_LL_GetURBState (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_LL_Stop (TYPE_5__*) ; 
 int /*<<< orphan*/  USBH_MAX_ERROR_COUNT ; 
 int /*<<< orphan*/  USBH_NOT_SUPPORTED ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USBH_URB_DONE ; 
 int /*<<< orphan*/  USBH_URB_ERROR ; 
 int /*<<< orphan*/  USBH_URB_IDLE ; 
 int /*<<< orphan*/  USBH_URB_NOTREADY ; 
 int /*<<< orphan*/  USBH_URB_STALL ; 
 int USB_D2H ; 
 int USB_REQ_DIR_MASK ; 
 int /*<<< orphan*/  osMessagePut (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_HandleControl (USBH_HandleTypeDef *phost)
{
  uint8_t direction;  
  USBH_StatusTypeDef status = USBH_BUSY;
  USBH_URBStateTypeDef URB_Status = USBH_URB_IDLE;
  
  switch (phost->Control.state)
  {
  case CTRL_SETUP:
    /* send a SETUP packet */
    USBH_CtlSendSetup     (phost, 
	                   (uint8_t *)phost->Control.setup.d8 , 
	                   phost->Control.pipe_out); 
    
    phost->Control.state = CTRL_SETUP_WAIT; 
    break; 
    
  case CTRL_SETUP_WAIT:
    
    URB_Status = USBH_LL_GetURBState(phost, phost->Control.pipe_out); 
    /* case SETUP packet sent successfully */
    if(URB_Status == USBH_URB_DONE)
    { 
      direction = (phost->Control.setup.b.bmRequestType & USB_REQ_DIR_MASK);
      
      /* check if there is a data stage */
      if (phost->Control.setup.b.wLength.w != 0 )
      {        
        if (direction == USB_D2H)
        {
          /* Data Direction is IN */
          phost->Control.state = CTRL_DATA_IN;
        }
        else
        {
          /* Data Direction is OUT */
          phost->Control.state = CTRL_DATA_OUT;
        } 
      }
      /* No DATA stage */
      else
      {
        /* If there is No Data Transfer Stage */
        if (direction == USB_D2H)
        {
          /* Data Direction is IN */
          phost->Control.state = CTRL_STATUS_OUT;
        }
        else
        {
          /* Data Direction is OUT */
          phost->Control.state = CTRL_STATUS_IN;
        } 
      }          
#if (USBH_USE_OS == 1)
      osMessagePut ( phost->os_event, USBH_CONTROL_EVENT, 0);
#endif
    }
    else if(URB_Status == USBH_URB_ERROR)
    {
      phost->Control.state = CTRL_ERROR;
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_CONTROL_EVENT, 0);
#endif      
    }    
    break;
    
  case CTRL_DATA_IN:  
    /* Issue an IN token */ 
     phost->Control.timer = phost->Timer;
    USBH_CtlReceiveData(phost,
                        phost->Control.buff, 
                        phost->Control.length,
                        phost->Control.pipe_in);
 
    phost->Control.state = CTRL_DATA_IN_WAIT;
    break;    
    
  case CTRL_DATA_IN_WAIT:
    
    URB_Status = USBH_LL_GetURBState(phost , phost->Control.pipe_in); 
    
    /* check is DATA packet transfered successfully */
    if  (URB_Status == USBH_URB_DONE)
    { 
      phost->Control.state = CTRL_STATUS_OUT;
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_CONTROL_EVENT, 0);
#endif      
    }
   
    /* manage error cases*/
    if  (URB_Status == USBH_URB_STALL) 
    { 
      /* In stall case, return to previous machine state*/
      status = USBH_NOT_SUPPORTED;
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_CONTROL_EVENT, 0);
#endif      
    }   
    else if (URB_Status == USBH_URB_ERROR)
    {
      /* Device error */
      phost->Control.state = CTRL_ERROR;  
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_CONTROL_EVENT, 0);
#endif      
    }
    break;
    
  case CTRL_DATA_OUT:
    
    USBH_CtlSendData (phost,
                      phost->Control.buff, 
                      phost->Control.length , 
                      phost->Control.pipe_out,
                      1);
     phost->Control.timer = phost->Timer;
    phost->Control.state = CTRL_DATA_OUT_WAIT;
    break;
    
  case CTRL_DATA_OUT_WAIT:
    
    URB_Status = USBH_LL_GetURBState(phost , phost->Control.pipe_out);     
    
    if  (URB_Status == USBH_URB_DONE)
    { /* If the Setup Pkt is sent successful, then change the state */
      phost->Control.state = CTRL_STATUS_IN;
#if (USBH_USE_OS == 1)
      osMessagePut ( phost->os_event, USBH_CONTROL_EVENT, 0);
#endif      
    }
    
    /* handle error cases */
    else if  (URB_Status == USBH_URB_STALL) 
    { 
      /* In stall case, return to previous machine state*/
      phost->Control.state = CTRL_STALLED; 
      status = USBH_NOT_SUPPORTED;
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_CONTROL_EVENT, 0);
#endif      
    } 
    else if  (URB_Status == USBH_URB_NOTREADY)
    { 
      /* Nack received from device */
      phost->Control.state = CTRL_DATA_OUT;
      
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_CONTROL_EVENT, 0);
#endif      
    }    
    else if (URB_Status == USBH_URB_ERROR)
    {
      /* device error */
      phost->Control.state = CTRL_ERROR;  
      status = USBH_FAIL;    
      
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_CONTROL_EVENT, 0);
#endif      
    } 
    break;
    
    
  case CTRL_STATUS_IN:
    /* Send 0 bytes out packet */
    USBH_CtlReceiveData (phost,
                         0,
                         0,
                         phost->Control.pipe_in);
    phost->Control.timer = phost->Timer;
    phost->Control.state = CTRL_STATUS_IN_WAIT;
    
    break;
    
  case CTRL_STATUS_IN_WAIT:
    
    URB_Status = USBH_LL_GetURBState(phost , phost->Control.pipe_in); 
    
    if  ( URB_Status == USBH_URB_DONE)
    { /* Control transfers completed, Exit the State Machine */
      phost->Control.state = CTRL_COMPLETE;
      status = USBH_OK;
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_CONTROL_EVENT, 0);
#endif      
    }
    
    else if (URB_Status == USBH_URB_ERROR)
    {
      phost->Control.state = CTRL_ERROR;
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_CONTROL_EVENT, 0);
#endif      
    }
     else if(URB_Status == USBH_URB_STALL)
    {
      /* Control transfers completed, Exit the State Machine */
      status = USBH_NOT_SUPPORTED;
      
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_CONTROL_EVENT, 0);
#endif      
    }
    break;
    
  case CTRL_STATUS_OUT:
    USBH_CtlSendData (phost,
                      0,
                      0,
                      phost->Control.pipe_out,
                      1);
     phost->Control.timer = phost->Timer;
    phost->Control.state = CTRL_STATUS_OUT_WAIT;
    break;
    
  case CTRL_STATUS_OUT_WAIT: 
    
    URB_Status = USBH_LL_GetURBState(phost , phost->Control.pipe_out);  
    if  (URB_Status == USBH_URB_DONE)
    { 
      status = USBH_OK;      
      phost->Control.state = CTRL_COMPLETE; 
      
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_CONTROL_EVENT, 0);
#endif      
    }
    else if  (URB_Status == USBH_URB_NOTREADY)
    { 
      phost->Control.state = CTRL_STATUS_OUT;
      
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_CONTROL_EVENT, 0);
#endif      
    }      
    else if (URB_Status == USBH_URB_ERROR)
    {
      phost->Control.state = CTRL_ERROR; 
      
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_CONTROL_EVENT, 0);
#endif      
    }
    break;
    
  case CTRL_ERROR:
    /* 
    After a halt condition is encountered or an error is detected by the 
    host, a control endpoint is allowed to recover by accepting the next Setup 
    PID; i.e., recovery actions via some other pipe are not required for control
    endpoints. For the Default Control Pipe, a device reset will ultimately be 
    required to clear the halt or error condition if the next Setup PID is not 
    accepted.
    */
    if (++ phost->Control.errorcount <= USBH_MAX_ERROR_COUNT)
    {
      /* try to recover control */
      USBH_LL_Stop(phost);
         
      /* Do the transmission again, starting from SETUP Packet */
      phost->Control.state = CTRL_SETUP; 
      phost->RequestState = CMD_SEND;
    }
    else
    {
      phost->Control.errorcount = 0;
      USBH_ErrLog("Control error");
      status = USBH_FAIL;
      
    }
    break;
    
  default:
    break;
  }
  return status;
}