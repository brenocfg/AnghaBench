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
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  char* DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  jsdisp_propput_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swprintf (char*,char const*,char*) ; 

HRESULT jsdisp_propput_idx(jsdisp_t *obj, DWORD idx, jsval_t val)
{
    WCHAR buf[12];

    static const WCHAR formatW[] = {'%','d',0};

    swprintf(buf, formatW, idx);
    return jsdisp_propput_name(obj, buf, val);
}