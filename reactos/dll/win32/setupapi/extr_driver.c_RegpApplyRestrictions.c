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
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__* PLONG ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_DATATYPE_MISMATCH ; 
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ ERROR_UNSUPPORTED_TYPE ; 
#define  REG_BINARY 134 
#define  REG_DWORD 133 
#define  REG_EXPAND_SZ 132 
#define  REG_MULTI_SZ 131 
#define  REG_NONE 130 
#define  REG_QWORD 129 
#define  REG_SZ 128 
 int RRF_RT_DWORD ; 
 int RRF_RT_QWORD ; 
 int RRF_RT_REG_BINARY ; 
 int RRF_RT_REG_DWORD ; 
 int RRF_RT_REG_EXPAND_SZ ; 
 int RRF_RT_REG_MULTI_SZ ; 
 int RRF_RT_REG_NONE ; 
 int RRF_RT_REG_QWORD ; 
 int RRF_RT_REG_SZ ; 

__attribute__((used)) static VOID
RegpApplyRestrictions( DWORD dwFlags, DWORD dwType, DWORD cbData,
                       PLONG ret )
{
    /* Check if the type is restricted by the passed flags */
    if (*ret == ERROR_SUCCESS || *ret == ERROR_MORE_DATA)
    {
        DWORD dwMask = 0;

        switch (dwType)
        {
        case REG_NONE: dwMask = RRF_RT_REG_NONE; break;
        case REG_SZ: dwMask = RRF_RT_REG_SZ; break;
        case REG_EXPAND_SZ: dwMask = RRF_RT_REG_EXPAND_SZ; break;
        case REG_MULTI_SZ: dwMask = RRF_RT_REG_MULTI_SZ; break;
        case REG_BINARY: dwMask = RRF_RT_REG_BINARY; break;
        case REG_DWORD: dwMask = RRF_RT_REG_DWORD; break;
        case REG_QWORD: dwMask = RRF_RT_REG_QWORD; break;
        }

        if (dwFlags & dwMask)
        {
            /* Type is not restricted, check for size mismatch */
            if (dwType == REG_BINARY)
            {
                DWORD cbExpect = 0;

                if ((dwFlags & RRF_RT_DWORD) == RRF_RT_DWORD)
                    cbExpect = 4;
                else if ((dwFlags & RRF_RT_QWORD) == RRF_RT_QWORD)
                    cbExpect = 8;

                if (cbExpect && cbData != cbExpect)
                    *ret = ERROR_DATATYPE_MISMATCH;
            }
        }
        else *ret = ERROR_UNSUPPORTED_TYPE;
    }
}