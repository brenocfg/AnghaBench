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
typedef  int uint32_t ;
struct vo {int dummy; } ;

/* Variables and functions */
#define  VOCTRL_CHECK_EVENTS 128 
 int VO_NOTIMPL ; 
 int VO_TRUE ; 
 int /*<<< orphan*/  check_events (struct vo*) ; 

__attribute__((used)) static int control(struct vo *vo, uint32_t request, void *data)
{
    switch (request) {
    case VOCTRL_CHECK_EVENTS:
        check_events(vo);
        return VO_TRUE;
    }
    return VO_NOTIMPL;
}