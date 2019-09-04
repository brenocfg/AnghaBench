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
struct TYPE_4__ {int checksum; int /*<<< orphan*/  checksum_type; } ;
typedef  TYPE_1__ TINF_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  TINF_CHKSUM_ADLER ; 
 int TINF_DATA_ERROR ; 
 unsigned char uzlib_get_byte (TYPE_1__*) ; 

int uzlib_zlib_parse_header(TINF_DATA *d)
{
   unsigned char cmf, flg;

   /* -- get header bytes -- */

   cmf = uzlib_get_byte(d);
   flg = uzlib_get_byte(d);

   /* -- check format -- */

   /* check checksum */
   if ((256*cmf + flg) % 31) return TINF_DATA_ERROR;

   /* check method is deflate */
   if ((cmf & 0x0f) != 8) return TINF_DATA_ERROR;

   /* check window size is valid */
   if ((cmf >> 4) > 7) return TINF_DATA_ERROR;

   /* check there is no preset dictionary */
   if (flg & 0x20) return TINF_DATA_ERROR;

   /* initialize for adler32 checksum */
   d->checksum_type = TINF_CHKSUM_ADLER;
   d->checksum = 1;

   return cmf >> 4;
}