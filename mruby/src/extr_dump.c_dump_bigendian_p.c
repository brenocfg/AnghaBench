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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  mrb_bool ;

/* Variables and functions */
#define  DUMP_ENDIAN_BIG 130 
#define  DUMP_ENDIAN_LIL 129 
#define  DUMP_ENDIAN_NAT 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bigendian_p () ; 

__attribute__((used)) static mrb_bool
dump_bigendian_p(uint8_t flags)
{
  switch (flags & DUMP_ENDIAN_NAT) {
  case DUMP_ENDIAN_BIG:
    return TRUE;
  case DUMP_ENDIAN_LIL:
    return FALSE;
  default:
  case DUMP_ENDIAN_NAT:
    return bigendian_p();
  }
}