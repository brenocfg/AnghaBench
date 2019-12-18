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
struct TYPE_3__ {int l; } ;
typedef  TYPE_1__ textfont_prop_val ;
typedef  enum textfont_prop_id { ____Placeholder_textfont_prop_id } textfont_prop_id ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  ITextFontImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  get_textfont_propl (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  set_textfont_prop (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
#define  tomFalse 131 
#define  tomToggle 130 
#define  tomTrue 129 
#define  tomUndefined 128 

__attribute__((used)) static HRESULT set_textfont_propd(ITextFontImpl *font, enum textfont_prop_id propid, LONG value)
{
    textfont_prop_val v;

    switch (value)
    {
    case tomUndefined:
        return S_OK;
    case tomToggle: {
        LONG oldvalue;
        get_textfont_propl(font, propid, &oldvalue);
        if (oldvalue == tomFalse)
            value = tomTrue;
        else if (oldvalue == tomTrue)
            value = tomFalse;
        else
            return E_INVALIDARG;
        /* fallthrough */
    }
    case tomTrue:
    case tomFalse:
        v.l = value;
        return set_textfont_prop(font, propid, &v);
    default:
        return E_INVALIDARG;
    }
}