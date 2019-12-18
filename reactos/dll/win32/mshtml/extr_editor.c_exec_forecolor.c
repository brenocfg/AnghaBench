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
typedef  int /*<<< orphan*/  nsICommandParams ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  HTMLDocument ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  NSCMD_FONTCOLOR ; 
 int /*<<< orphan*/  NSSTATE_ATTRIBUTE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UPDATE_UI ; 
 scalar_t__ VT_I4 ; 
 int V_I4 (int /*<<< orphan*/ *) ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_nscommand_params () ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_ns_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsICommandParams_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsICommandParams_SetCStringValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int) ; 
 int /*<<< orphan*/  update_doc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT exec_forecolor(HTMLDocument *This, DWORD cmdexecopt, VARIANT *in, VARIANT *out)
{
    TRACE("(%p)->(%p %p)\n", This, in, out);

    if(in) {
        if(V_VT(in) == VT_I4) {
            nsICommandParams *nsparam = create_nscommand_params();
            char color_str[10];

            sprintf(color_str, "#%02x%02x%02x",
                    V_I4(in)&0xff, (V_I4(in)>>8)&0xff, (V_I4(in)>>16)&0xff);

            nsICommandParams_SetCStringValue(nsparam, NSSTATE_ATTRIBUTE, color_str);
            do_ns_command(This, NSCMD_FONTCOLOR, nsparam);

            nsICommandParams_Release(nsparam);
        }else {
            FIXME("unsupported forecolor %s\n", debugstr_variant(in));
        }

        update_doc(This, UPDATE_UI);
    }

    if(out) {
        FIXME("unsupported out\n");
        return E_NOTIMPL;
    }

    return S_OK;
}