#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
struct TYPE_4__ {scalar_t__ curLen; int /*<<< orphan*/  (* get_byte ) () ;int /*<<< orphan*/  (* put_byte ) (int /*<<< orphan*/ ) ;scalar_t__ bitcount; } ;
typedef  TYPE_1__ UZLIB_DATA ;

/* Variables and functions */
 int UZLIB_DATA_ERROR ; 
 int UZLIB_DONE ; 
 int UZLIB_OK ; 
 int get_uint16 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 () ; 

__attribute__((used)) static int inflate_uncompressed_block (UZLIB_DATA *d) {
  if (d->curLen == 0) {
    uint length    = get_uint16(d);
    uint invlength = get_uint16(d);

    /* check length */
    if (length != (~invlength & 0x0000ffff))
      return UZLIB_DATA_ERROR;

    /* increment length to properly return UZLIB_DONE below, without
       producing data at the same time */
    d->curLen = length + 1;

    /* make sure we start next block on a byte boundary */
    d->bitcount = 0;
  }

  if (--d->curLen == 0) {
    return UZLIB_DONE;
  }

  d->put_byte(d->get_byte());
  return UZLIB_OK;
}