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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_JScript ; 
 int /*<<< orphan*/  CoGetClassObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static BOOL is_jscript_available(void)
{
    static BOOL available, checked;

    if(!checked) {
        IUnknown *unk;
        HRESULT hres = CoGetClassObject(&CLSID_JScript, CLSCTX_INPROC_SERVER, NULL, &IID_IUnknown, (void**)&unk);

        if(SUCCEEDED(hres)) {
            available = TRUE;
            IUnknown_Release(unk);
        }else {
            available = FALSE;
        }
        checked = TRUE;
    }

    return available;
}