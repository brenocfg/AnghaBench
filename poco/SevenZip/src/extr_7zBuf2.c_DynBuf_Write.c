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
struct TYPE_8__ {size_t size; size_t pos; int /*<<< orphan*/  const* data; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* Free ) (TYPE_1__*,int /*<<< orphan*/  const*) ;scalar_t__ (* Alloc ) (TYPE_1__*,size_t) ;} ;
typedef  TYPE_1__ ISzAlloc ;
typedef  TYPE_2__ CDynBuf ;
typedef  int /*<<< orphan*/  const Byte ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ stub1 (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/  const*) ; 

int DynBuf_Write(CDynBuf *p, const Byte *buf, size_t size, ISzAlloc *alloc)
{
  if (size > p->size - p->pos)
  {
    size_t newSize = p->pos + size;
    Byte *data;
    newSize += newSize / 4;
    data = (Byte *)alloc->Alloc(alloc, newSize);
    if (data == 0)
      return 0;
    p->size = newSize;
    memcpy(data, p->data, p->pos);
    alloc->Free(alloc, p->data);
    p->data = data;
  }
  memcpy(p->data + p->pos, buf, size);
  p->pos += size;
  return 1;
}