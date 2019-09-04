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
typedef  int /*<<< orphan*/  PORTS_MODULE_ID ;
typedef  int /*<<< orphan*/  PORTS_CHANGE_NOTICE_PIN ;

/* Variables and functions */

void SYS_PORTS_ChangeNotificationDisable( PORTS_MODULE_ID index,
                                          PORTS_CHANGE_NOTICE_PIN pinNum )
{
#if defined(PLIB_PORTS_ExistsPinChangeNotice)
    if(PLIB_PORTS_ExistsPinChangeNotice(index))
    {
        PLIB_PORTS_PinChangeNoticeDisable( index, pinNum );
    }
#endif
}