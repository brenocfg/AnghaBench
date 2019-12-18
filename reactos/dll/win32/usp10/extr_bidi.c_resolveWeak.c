#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int length; scalar_t__ sos; TYPE_1__* item; } ;
struct TYPE_6__ {scalar_t__* pcls; } ;
typedef  TYPE_2__ IsolatedRun ;

/* Variables and functions */
 scalar_t__ AL ; 
 scalar_t__ AN ; 
 scalar_t__ BN ; 
 scalar_t__ CS ; 
 scalar_t__ EN ; 
 scalar_t__ ES ; 
 scalar_t__ ET ; 
 scalar_t__ L ; 
 scalar_t__ LRI ; 
 scalar_t__ NSM ; 
 scalar_t__ ON ; 
 scalar_t__ R ; 
 int iso_nextValidChar (TYPE_2__*,int) ; 
 int iso_previousValidChar (TYPE_2__*,int) ; 

__attribute__((used)) static void resolveWeak(IsolatedRun * iso_run)
{
    int i;

    /* W1 */
    for (i=0; i < iso_run->length; i++)
    {
        if (*iso_run->item[i].pcls == NSM)
        {
            int j = iso_previousValidChar(iso_run, i);
            if (j == -1)
                *iso_run->item[i].pcls = iso_run->sos;
            else if (*iso_run->item[j].pcls >= LRI)
                *iso_run->item[i].pcls = ON;
            else
                *iso_run->item[i].pcls = *iso_run->item[j].pcls;
        }
    }

    /* W2 */
    for (i = 0; i < iso_run->length; i++)
    {
        if (*iso_run->item[i].pcls == EN)
        {
            int j = iso_previousValidChar(iso_run, i);
            while (j > -1)
            {
                if (*iso_run->item[j].pcls == R || *iso_run->item[j].pcls == L || *iso_run->item[j].pcls == AL)
                {
                    if (*iso_run->item[j].pcls == AL)
                        *iso_run->item[i].pcls = AN;
                    break;
                }
                j = iso_previousValidChar(iso_run, j);
            }
        }
    }

    /* W3 */
    for (i = 0; i < iso_run->length; i++)
    {
        if (*iso_run->item[i].pcls == AL)
            *iso_run->item[i].pcls = R;
    }

    /* W4 */
    for (i = 0; i < iso_run->length; i++)
    {
        if (*iso_run->item[i].pcls == ES)
        {
            int b = iso_previousValidChar(iso_run, i);
            int f = iso_nextValidChar(iso_run, i);

            if (b > -1 && f > -1 && *iso_run->item[b].pcls == EN && *iso_run->item[f].pcls == EN)
                *iso_run->item[i].pcls = EN;
        }
        else if (*iso_run->item[i].pcls == CS)
        {
            int b = iso_previousValidChar(iso_run, i);
            int f = iso_nextValidChar(iso_run, i);

            if (b > -1 && f > -1 && *iso_run->item[b].pcls == EN && *iso_run->item[f].pcls == EN)
                *iso_run->item[i].pcls = EN;
            else if (b > -1 && f > -1 && *iso_run->item[b].pcls == AN && *iso_run->item[f].pcls == AN)
                *iso_run->item[i].pcls = AN;
        }
    }

    /* W5 */
    for (i = 0; i < iso_run->length; i++)
    {
        if (*iso_run->item[i].pcls == ET)
        {
            int j;
            for (j = i-1 ; j > -1; j--)
            {
                if (*iso_run->item[j].pcls == BN) continue;
                if (*iso_run->item[j].pcls == ET) continue;
                else if (*iso_run->item[j].pcls == EN) *iso_run->item[i].pcls = EN;
                else break;
            }
            if (*iso_run->item[i].pcls == ET)
            {
                for (j = i+1; j < iso_run->length; j++)
                {
                    if (*iso_run->item[j].pcls == BN) continue;
                    if (*iso_run->item[j].pcls == ET) continue;
                    else if (*iso_run->item[j].pcls == EN) *iso_run->item[i].pcls = EN;
                    else break;
                }
            }
        }
    }

    /* W6 */
    for (i = 0; i < iso_run->length; i++)
    {
        if (*iso_run->item[i].pcls == ET || *iso_run->item[i].pcls == ES || *iso_run->item[i].pcls == CS || *iso_run->item[i].pcls == ON)
        {
            int b = i-1;
            int f = i+1;
            if (b > -1 && *iso_run->item[b].pcls == BN)
                *iso_run->item[b].pcls = ON;
            if (f < iso_run->length && *iso_run->item[f].pcls == BN)
                *iso_run->item[f].pcls = ON;

            *iso_run->item[i].pcls = ON;
        }
    }

    /* W7 */
    for (i = 0; i < iso_run->length; i++)
    {
        if (*iso_run->item[i].pcls == EN)
        {
            int j;
            for (j = iso_previousValidChar(iso_run, i); j > -1; j = iso_previousValidChar(iso_run, j))
                if (*iso_run->item[j].pcls == R || *iso_run->item[j].pcls == L)
                {
                    if (*iso_run->item[j].pcls == L)
                        *iso_run->item[i].pcls = L;
                    break;
                }
            if (iso_run->sos == L &&  j == -1)
                *iso_run->item[i].pcls = L;
        }
    }
}