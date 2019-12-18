#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ cbMessages; scalar_t__ cMessages; } ;
struct TYPE_5__ {int state; int /*<<< orphan*/  valid_info; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ POP3Transport ;
typedef  TYPE_2__ POP3STAT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 void* STATE_DONE ; 
#define  STATE_OK 128 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  sscanf (char*,char*,scalar_t__*,scalar_t__*) ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static HRESULT parse_stat_response(POP3Transport *This, POP3STAT *stat)
{
    char *p;

    stat->cMessages = 0;
    stat->cbMessages = 0;
    switch (This->state)
    {
    case STATE_OK:
        if ((p = strchr(This->ptr, ' ')))
        {
            while (*p == ' ') p++;
            sscanf(p, "%u %u", &stat->cMessages, &stat->cbMessages);
            This->valid_info = TRUE;
            This->state = STATE_DONE;
            return S_OK;
        }

    default:
        WARN("parse error\n");
        This->state = STATE_DONE;
        return S_FALSE;
    }
}