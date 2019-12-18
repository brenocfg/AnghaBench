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
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int PROPF_CONFIGURABLE ; 
 int PROPF_WRITABLE ; 
 int /*<<< orphan*/  jsdisp_define_data_property (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT set_constructor_prop(script_ctx_t *ctx, jsdisp_t *constr, jsdisp_t *prot)
{
    static const WCHAR constructorW[] = {'c','o','n','s','t','r','u','c','t','o','r',0};

    return jsdisp_define_data_property(prot, constructorW, PROPF_WRITABLE | PROPF_CONFIGURABLE,
                                       jsval_obj(constr));
}