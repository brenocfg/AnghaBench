#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int state; int /*<<< orphan*/  response; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ POP3Transport ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 void* STATE_DONE ; 
#define  STATE_NONE 128 
 int STATE_OK ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT parse_response(POP3Transport *This)
{
    switch (This->state)
    {
    case STATE_NONE:
        if (strlen(This->response) < 3)
        {
            WARN("parse error\n");
            This->state = STATE_DONE;
            return S_FALSE;
        }
        if (!memcmp(This->response, "+OK", 3))
        {
            This->ptr = This->response + 3;
            This->state = STATE_OK;
            return S_OK;
        }
        This->state = STATE_DONE;
        return S_FALSE;

    default: return S_OK;
    }
}