#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int dwNumObjs; } ;
struct TYPE_7__ {int dwType; } ;
typedef  TYPE_1__* LPDIOBJECTDATAFORMAT ;
typedef  TYPE_2__* LPCDIDATAFORMAT ;
typedef  int DWORD ;

/* Variables and functions */
 TYPE_1__* dataformat_to_odf (TYPE_2__*,int) ; 

LPDIOBJECTDATAFORMAT dataformat_to_odf_by_type(LPCDIDATAFORMAT df, int n, DWORD type)
{
    int i, nfound = 0;

    for (i=0; i < df->dwNumObjs; i++)
    {
        LPDIOBJECTDATAFORMAT odf = dataformat_to_odf(df, i);

        if (odf->dwType & type)
        {
            if (n == nfound)
                return odf;

            nfound++;
        }
    }

    return NULL;
}