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
typedef  int /*<<< orphan*/  mbi ;
struct TYPE_3__ {scalar_t__ AllocationBase; } ;
typedef  TYPE_1__ MEMORY_BASIC_INFORMATION ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetModuleFileNameA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 size_t MAXDWORD ; 
 int VirtualQuery (void const*,TYPE_1__*,int) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static const char*
_module_name_from_addr(const void* addr, void **module_start_addr,
                       char* psz, size_t nChars, char** module_name)
{
    MEMORY_BASIC_INFORMATION mbi;

    if ((nChars > MAXDWORD) ||
        (VirtualQuery(addr, &mbi, sizeof(mbi)) != sizeof(mbi)) ||
        !GetModuleFileNameA((HMODULE)mbi.AllocationBase, psz, (DWORD)nChars))
    {
        psz[0] = '\0';
        *module_name = psz;
        *module_start_addr = 0;
    }
    else
    {
        char* s1 = strrchr(psz, '\\'), *s2 = strrchr(psz, '/');
        if (s2 && !s1)
            s1 = s2;
        else if (s1 && s2 && s1 < s2)
            s1 = s2;

        if (!s1)
            s1 = psz;
        else
            s1++;

        *module_name = s1;
        *module_start_addr = (void *)mbi.AllocationBase;
    }
    return psz;
}