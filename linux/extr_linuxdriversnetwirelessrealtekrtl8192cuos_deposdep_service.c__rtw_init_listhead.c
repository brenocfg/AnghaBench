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
typedef  int /*<<< orphan*/  _list ;

/* Variables and functions */

void _rtw_init_listhead(_list *list)
{

#ifdef PLATFORM_LINUX

        INIT_LIST_HEAD(list);

#endif

#ifdef PLATFORM_FREEBSD
         list->next = list;
         list->prev = list;
#endif
#ifdef PLATFORM_WINDOWS

        NdisInitializeListHead(list);

#endif

}