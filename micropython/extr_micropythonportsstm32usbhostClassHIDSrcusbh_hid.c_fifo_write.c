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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {int lock; int head; int tail; int size; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ FIFO_TypeDef ;

/* Variables and functions */

uint16_t  fifo_write(FIFO_TypeDef * f, const void * buf, uint16_t  nbytes)
{
  uint16_t  i;
  const uint8_t * p;
  p = buf;
  if(f->lock == 0)
  {
    f->lock = 1;
    for(i=0; i < nbytes; i++)
    {
      if( (f->head + 1 == f->tail) ||
         ( (f->head + 1 == f->size) && (f->tail == 0)) )
      {
        f->lock = 0;
        return i;
      } 
      else 
      {
        f->buf[f->head] = *p++;
        f->head++;
        if( f->head == f->size )
        {
          f->head = 0;
        }
      }
    }
  }
  f->lock = 0;
  return nbytes;
}