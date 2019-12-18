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
 int INTERNAL_FLASH_WRITE_UNIT_SIZE ; 
 int /*<<< orphan*/  platform_s_flash_read (char*,int const,int const) ; 
 int const platform_s_flash_write (char const*,int const,int const) ; 

uint32_t platform_flash_write( const void *from, uint32_t toaddr, uint32_t size )
{
#ifndef INTERNAL_FLASH_WRITE_UNIT_SIZE
  return platform_s_flash_write( from, toaddr, size );
#else // #ifindef INTERNAL_FLASH_WRITE_UNIT_SIZE
  uint32_t temp, rest, ssize = size;
  unsigned i;
  char tmpdata[ INTERNAL_FLASH_WRITE_UNIT_SIZE ];
  const uint8_t *pfrom = ( const uint8_t* )from;
  const uint32_t blksize = INTERNAL_FLASH_WRITE_UNIT_SIZE;
  const uint32_t blkmask = INTERNAL_FLASH_WRITE_UNIT_SIZE - 1;

  // Align the start
  if( toaddr & blkmask )
  {
    rest = toaddr & blkmask;
    temp = toaddr & ~blkmask; // this is the actual aligned address
    // memcpy( tmpdata, ( const void* )temp, blksize );
    platform_s_flash_read( tmpdata, temp, blksize );
    for( i = rest; size && ( i < blksize ); i ++, size --, pfrom ++ )
      tmpdata[ i ] = *pfrom;
    platform_s_flash_write( tmpdata, temp, blksize );
    if( size == 0 )
      return ssize;
    toaddr = temp + blksize;
  }
  // The start address is now a multiple of blksize
  // Compute how many bytes we can write as multiples of blksize
  rest = size & blkmask;
  temp = size & ~blkmask;
  // Program the blocks now
  if( temp )
  {
    platform_s_flash_write( pfrom, toaddr, temp );
    toaddr += temp;
    pfrom += temp;
  }
  // And the final part of a block if needed
  if( rest )
  {
    // memcpy( tmpdata, ( const void* )toaddr, blksize );
    platform_s_flash_read( tmpdata, toaddr, blksize );
    for( i = 0; size && ( i < rest ); i ++, size --, pfrom ++ )
      tmpdata[ i ] = *pfrom;
    platform_s_flash_write( tmpdata, toaddr, blksize );
  }
  return ssize;
#endif // #ifndef INTERNAL_FLASH_WRITE_UNIT_SIZE
}