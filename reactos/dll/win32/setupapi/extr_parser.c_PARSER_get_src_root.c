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
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  HINF ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__* get_inf_dir (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,unsigned int) ; 

WCHAR *PARSER_get_src_root( HINF hinf )
{
    unsigned int len;
    const WCHAR *dir = get_inf_dir( hinf, &len );
    WCHAR *ret = HeapAlloc( GetProcessHeap(), 0, (len + 1) * sizeof(WCHAR) );
    if (ret)
    {
        memcpy( ret, dir, len * sizeof(WCHAR) );
        ret[len] = 0;
    }
    return ret;
}