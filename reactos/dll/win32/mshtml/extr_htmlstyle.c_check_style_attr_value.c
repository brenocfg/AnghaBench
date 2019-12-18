#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t styleid_t ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  int /*<<< orphan*/  VARIANT_BOOL ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  nsstyle; } ;
typedef  int /*<<< orphan*/  PRUnichar ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_1__ HTMLStyle ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARIANT_FALSE ; 
 int /*<<< orphan*/  VARIANT_TRUE ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_nsstyle_attr_nsval (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_GetData (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  nsAString_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmpW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 TYPE_2__* style_tbl ; 

__attribute__((used)) static HRESULT check_style_attr_value(HTMLStyle *This, styleid_t sid, LPCWSTR exval, VARIANT_BOOL *p)
{
    nsAString str_value;
    const PRUnichar *value;

    nsAString_Init(&str_value, NULL);

    get_nsstyle_attr_nsval(This->nsstyle, sid, &str_value);

    nsAString_GetData(&str_value, &value);
    *p = strcmpW(value, exval) ? VARIANT_FALSE : VARIANT_TRUE;
    nsAString_Finish(&str_value);

    TRACE("%s -> %x\n", debugstr_w(style_tbl[sid].name), *p);
    return S_OK;
}