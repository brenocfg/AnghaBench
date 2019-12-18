#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_5__ {int /*<<< orphan*/  Inf; } ;
typedef  int /*<<< orphan*/  INT ;
typedef  TYPE_1__ INFCONTEXT ;
typedef  unsigned int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SetupGetIntField (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupGetStringFieldW (TYPE_1__*,int,char*,unsigned int,unsigned int*) ; 
 char* get_dirid_subst (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 

WCHAR *PARSER_get_dest_dir( INFCONTEXT *context )
{
    const WCHAR *dir;
    WCHAR *ptr, *ret;
    INT dirid;
    unsigned int len1;
    DWORD len2;

    if (!SetupGetIntField( context, 1, &dirid )) return NULL;
    if (!(dir = get_dirid_subst( context->Inf, dirid, &len1 ))) return NULL;
    if (!SetupGetStringFieldW( context, 2, NULL, 0, &len2 )) len2 = 0;
    if (!(ret = HeapAlloc( GetProcessHeap(), 0, (len1+len2+1) * sizeof(WCHAR) ))) return NULL;
    memcpy( ret, dir, len1 * sizeof(WCHAR) );
    ptr = ret + len1;
    if (len2 && ptr > ret && ptr[-1] != '\\') *ptr++ = '\\';
    if (!SetupGetStringFieldW( context, 2, ptr, len2, NULL )) *ptr = 0;
    return ret;
}