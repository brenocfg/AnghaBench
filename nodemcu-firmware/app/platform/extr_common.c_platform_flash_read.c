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
typedef  char uint8_t ;
typedef  int const uint32_t ;

/* Variables and functions */
 int INTERNAL_FLASH_READ_UNIT_SIZE ; 
 int const platform_s_flash_read (char*,int const,int const) ; 

uint32_t platform_flash_read( void *to, uint32_t fromaddr, uint32_t size )
{
#ifndef INTERNAL_FLASH_READ_UNIT_SIZE
  return platform_s_flash_read( to, fromaddr, size );
#else // #ifindef INTERNAL_FLASH_READ_UNIT_SIZE
  uint32_t temp, rest, ssize = size;
  unsigned i;
  char tmpdata[ INTERNAL_FLASH_READ_UNIT_SIZE ] __attribute__ ((aligned(INTERNAL_FLASH_READ_UNIT_SIZE)));
  uint8_t *pto = ( uint8_t* )to;
  const uint32_t blksize = INTERNAL_FLASH_READ_UNIT_SIZE;
  const uint32_t blkmask = INTERNAL_FLASH_READ_UNIT_SIZE - 1;

  // Align the start
  if( fromaddr & blkmask )
  {
    rest = fromaddr & blkmask;
    temp = fromaddr & ~blkmask; // this is the actual aligned address
    platform_s_flash_read( tmpdata, temp, blksize );
    for( i = rest; size && ( i < blksize ); i ++, size --, pto ++ )
      *pto = tmpdata[ i ];

    if( size == 0 )
      return ssize;
    fromaddr = temp + blksize;
  }
  // The start address is now a multiple of blksize
  // Compute how many bytes we can read as multiples of blksize
  rest = size & blkmask;
  temp = size & ~blkmask;
  // Program the blocks now
  if( temp )
  {
    platform_s_flash_read( pto, fromaddr, temp );
    fromaddr += temp;
    pto += temp;
  }
  // And the final part of a block if needed
  if( rest )
  {
    platform_s_flash_read( tmpdata, fromaddr, blksize );
    for( i = 0; size && ( i < rest ); i ++, size --, pto ++ )
      *pto = tmpdata[ i ];
  }
  return ssize;
#endif // #ifndef INTERNAL_FLASH_READ_UNIT_SIZE
}