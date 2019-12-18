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
struct TYPE_4__ {int /*<<< orphan*/ * ptd; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pAdvSink; TYPE_1__ formatetc; } ;
typedef  TYPE_2__ STATDATA ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAdviseSink_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_statdata(STATDATA *data)
{
    CoTaskMemFree(data->formatetc.ptd);
    data->formatetc.ptd = NULL;

    if(data->pAdvSink)
    {
        IAdviseSink_Release(data->pAdvSink);
        data->pAdvSink = NULL;
    }
}