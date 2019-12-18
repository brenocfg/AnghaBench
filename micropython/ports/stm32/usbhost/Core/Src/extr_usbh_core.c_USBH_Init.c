#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_8__ {void (* pUser ) (TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  thread; int /*<<< orphan*/  os_event; scalar_t__ ClassNumber; int /*<<< orphan*/ * pActiveClass; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ USBH_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  DeInitStateMachine (TYPE_1__*) ; 
 int /*<<< orphan*/  USBH_ErrLog (char*) ; 
 int /*<<< orphan*/  USBH_FAIL ; 
 int /*<<< orphan*/  USBH_LL_Init (TYPE_1__*) ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USBH_PROCESS_PRIO ; 
 int /*<<< orphan*/  USBH_Process_OS ; 
 int /*<<< orphan*/  USBH_Queue ; 
 int /*<<< orphan*/  USBH_Thread ; 
 int configMINIMAL_STACK_SIZE ; 
 int /*<<< orphan*/  osMessageCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osMessageQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osMessageQDef (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osThreadCreate (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  osThreadDef (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uint16_t ; 

USBH_StatusTypeDef  USBH_Init(USBH_HandleTypeDef *phost, void (*pUsrFunc)(USBH_HandleTypeDef *phost, uint8_t ), uint8_t id)
{
  /* Check whether the USB Host handle is valid */
  if(phost == NULL)
  {
    USBH_ErrLog("Invalid Host handle");
    return USBH_FAIL; 
  }
  
  /* Set DRiver ID */
  phost->id = id;
  
  /* Unlink class*/
  phost->pActiveClass = NULL;
  phost->ClassNumber = 0;
  
  /* Restore default states and prepare EP0 */ 
  DeInitStateMachine(phost);
  
  /* Assign User process */
  if(pUsrFunc != NULL)
  {
    phost->pUser = pUsrFunc;
  }
  
#if (USBH_USE_OS == 1) 
  
  /* Create USB Host Queue */
  osMessageQDef(USBH_Queue, 10, uint16_t);
  phost->os_event = osMessageCreate (osMessageQ(USBH_Queue), NULL); 
  
  /*Create USB Host Task */
  osThreadDef(USBH_Thread, USBH_Process_OS, USBH_PROCESS_PRIO, 0, 8 * configMINIMAL_STACK_SIZE);
  phost->thread = osThreadCreate (osThread(USBH_Thread), phost);
#endif  
  
  /* Initialize low level driver */
  USBH_LL_Init(phost);
  return USBH_OK;
}