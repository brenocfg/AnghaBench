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
struct TYPE_3__ {int /*<<< orphan*/  sink_cookie; scalar_t__ sink_dispatch; int /*<<< orphan*/  sink_id; int /*<<< orphan*/  v; } ;
typedef  TYPE_1__ php_com_dotnet_object ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IConnectionPointContainer ;
typedef  int /*<<< orphan*/  IConnectionPoint ;

/* Variables and functions */
 int /*<<< orphan*/  IConnectionPointContainer_FindConnectionPoint (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IConnectionPointContainer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IConnectionPoint_Advise (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IConnectionPoint_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IConnectionPoint_Unadvise (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDispatch_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IConnectionPointContainer ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_DISPATCH (int /*<<< orphan*/ *) ; 

void php_com_object_enable_event_sink(php_com_dotnet_object *obj, int enable)
{
	if (obj->sink_dispatch) {
		IConnectionPointContainer *cont;
		IConnectionPoint *point;

		if (SUCCEEDED(IDispatch_QueryInterface(V_DISPATCH(&obj->v),
				&IID_IConnectionPointContainer, (void**)&cont))) {

			if (SUCCEEDED(IConnectionPointContainer_FindConnectionPoint(cont,
					&obj->sink_id, &point))) {

				if (enable) {
					IConnectionPoint_Advise(point, (IUnknown*)obj->sink_dispatch, &obj->sink_cookie);
				} else {
					IConnectionPoint_Unadvise(point, obj->sink_cookie);
				}
				IConnectionPoint_Release(point);
			}
			IConnectionPointContainer_Release(cont);
		}
	}
}