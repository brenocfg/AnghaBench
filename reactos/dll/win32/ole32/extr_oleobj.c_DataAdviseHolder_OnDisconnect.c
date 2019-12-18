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
struct TYPE_5__ {size_t maxCons; int /*<<< orphan*/ * delegate; TYPE_1__* connections; scalar_t__* remote_connections; } ;
struct TYPE_4__ {int advf; int /*<<< orphan*/ * pAdvSink; } ;
typedef  int /*<<< orphan*/  IDataAdviseHolder ;
typedef  TYPE_2__ DataAdviseHolder ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  IDataObject_DUnadvise (int /*<<< orphan*/ *,scalar_t__) ; 
 int WINE_ADVF_REMOTE ; 
 TYPE_2__* impl_from_IDataAdviseHolder (int /*<<< orphan*/ *) ; 

void DataAdviseHolder_OnDisconnect(IDataAdviseHolder *iface)
{
  DataAdviseHolder *This = impl_from_IDataAdviseHolder(iface);
  DWORD index;

  for(index = 0; index < This->maxCons; index++)
  {
    if((This->connections[index].pAdvSink != NULL) &&
       (This->connections[index].advf & WINE_ADVF_REMOTE))
    {
      IDataObject_DUnadvise(This->delegate, This->remote_connections[index]);
      This->remote_connections[index] = 0;
      This->connections[index].advf &= ~WINE_ADVF_REMOTE;
    }
  }
  This->delegate = NULL;
}