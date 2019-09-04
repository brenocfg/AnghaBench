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
typedef  int /*<<< orphan*/  SYS_PORTS_PULLUP_PULLDOWN_STATUS ;
typedef  int /*<<< orphan*/  PORTS_MODULE_ID ;
typedef  int /*<<< orphan*/  PORTS_CHANGE_NOTICE_PIN ;

/* Variables and functions */

void SYS_PORTS_ChangeNotificationEnable( PORTS_MODULE_ID index,
                                         PORTS_CHANGE_NOTICE_PIN pinNum,
                                         SYS_PORTS_PULLUP_PULLDOWN_STATUS value )
{
#if defined(PLIB_PORTS_ExistsChangeNoticePullUp)
    if(PLIB_PORTS_ExistsChangeNoticePullUp(index))
    {
        switch(value)
        {
            case SYS_PORTS_PULLUP_DISABLE:
                PLIB_PORTS_ChangeNoticePullUpDisable(index, pinNum);
                break;
            case SYS_PORTS_PULLUP_ENABLE:
                PLIB_PORTS_ChangeNoticePullUpEnable(index, pinNum);
                break;
        }
    }
#endif

#if defined(PLIB_PORTS_ExistsPinChangeNotice)
    if(PLIB_PORTS_ExistsPinChangeNotice(index))
    {
        PLIB_PORTS_PinChangeNoticeEnable( index, pinNum );
    }
#endif
}