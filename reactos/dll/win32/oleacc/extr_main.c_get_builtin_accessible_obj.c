#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * accessible_create ;
struct TYPE_7__ {int idx; int /*<<< orphan*/ * create_window; int /*<<< orphan*/ * create_client; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ WCHAR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 scalar_t__ OBJID_CLIENT ; 
 int /*<<< orphan*/  OBJID_QUERYCLASSNAMEIDX ; 
 int /*<<< orphan*/  RealGetWindowClassW (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 int /*<<< orphan*/  WM_GETOBJECT ; 
 TYPE_1__* builtin_classes ; 
 int debugstr_w (TYPE_1__*) ; 
 int /*<<< orphan*/  strcmpiW (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static accessible_create get_builtin_accessible_obj(HWND hwnd, LONG objid)
{
    WCHAR class_name[64];
    int i, idx;

    if(!RealGetWindowClassW(hwnd, class_name, ARRAY_SIZE(class_name)))
        return NULL;
    TRACE("got window class: %s\n", debugstr_w(class_name));

    for(i=0; i<ARRAY_SIZE(builtin_classes); i++) {
        if(!strcmpiW(class_name, builtin_classes[i].name)) {
            accessible_create ret;

            ret = (objid==OBJID_CLIENT ?
                    builtin_classes[i].create_client :
                    builtin_classes[i].create_window);
            if(!ret)
                FIXME("unhandled window class: %s\n", debugstr_w(class_name));
            return ret;
        }
    }

    idx = SendMessageW(hwnd, WM_GETOBJECT, 0, OBJID_QUERYCLASSNAMEIDX);
    if(idx) {
        for(i=0; i<ARRAY_SIZE(builtin_classes); i++) {
            if(idx == builtin_classes[i].idx) {
                accessible_create ret;

                ret = (objid==OBJID_CLIENT ?
                        builtin_classes[i].create_client :
                        builtin_classes[i].create_window);
                if(!ret)
                    FIXME("unhandled class name idx: %x\n", idx);
                return ret;
            }
        }

        WARN("unhandled class name idx: %x\n", idx);
    }

    return NULL;
}