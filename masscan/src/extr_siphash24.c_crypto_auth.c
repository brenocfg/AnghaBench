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
typedef  unsigned char u8 ;
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SIPROUND ; 
 int /*<<< orphan*/  U64TO8_LE (unsigned char*,int) ; 
 int U8TO64_LE (unsigned char const*) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 

__attribute__((used)) static int crypto_auth( unsigned char *out, const unsigned char *in, unsigned long long inlen, const unsigned char *k )
{
  /* "somepseudorandomlygeneratedbytes" */
  u64 v0 = 0x736f6d6570736575ULL;
  u64 v1 = 0x646f72616e646f6dULL;
  u64 v2 = 0x6c7967656e657261ULL;
  u64 v3 = 0x7465646279746573ULL;
  u64 b;
  u64 k0 = U8TO64_LE( k );
  u64 k1 = U8TO64_LE( k + 8 );
  const u8 *end = in + inlen - ( inlen % sizeof( u64 ) );
  const int left = inlen & 7;
  b = ( ( u64 )inlen ) << 56;
  v3 ^= k1;
  v2 ^= k0;
  v1 ^= k1;
  v0 ^= k0;

  for ( ; in != end; in += 8 )
  {
    u64 m;
    m = U8TO64_LE( in );
#ifdef xxxDEBUG
    printf( "(%3d) v0 %08x %08x\n", ( int )inlen, ( u32 )( v0 >> 32 ), ( u32 )v0 );
    printf( "(%3d) v1 %08x %08x\n", ( int )inlen, ( u32 )( v1 >> 32 ), ( u32 )v1 );
    printf( "(%3d) v2 %08x %08x\n", ( int )inlen, ( u32 )( v2 >> 32 ), ( u32 )v2 );
    printf( "(%3d) v3 %08x %08x\n", ( int )inlen, ( u32 )( v3 >> 32 ), ( u32 )v3 );
    printf( "(%3d) compress %08x %08x\n", ( int )inlen, ( u32 )( m >> 32 ), ( u32 )m );
#endif
    v3 ^= m;
    SIPROUND;
    SIPROUND;
    v0 ^= m;
  }

  switch( left )
  {
  case 7: b |= ( ( u64 )in[ 6] )  << 48;
  case 6: b |= ( ( u64 )in[ 5] )  << 40;
  case 5: b |= ( ( u64 )in[ 4] )  << 32;
  case 4: b |= ( ( u64 )in[ 3] )  << 24;
  case 3: b |= ( ( u64 )in[ 2] )  << 16;
  case 2: b |= ( ( u64 )in[ 1] )  <<  8;
  case 1: b |= ( ( u64 )in[ 0] ); break;
  case 0: break;
  }

#ifdef xxxDEBUG
  printf( "(%3d) v0 %08x %08x\n", ( int )inlen, ( u32 )( v0 >> 32 ), ( u32 )v0 );
  printf( "(%3d) v1 %08x %08x\n", ( int )inlen, ( u32 )( v1 >> 32 ), ( u32 )v1 );
  printf( "(%3d) v2 %08x %08x\n", ( int )inlen, ( u32 )( v2 >> 32 ), ( u32 )v2 );
  printf( "(%3d) v3 %08x %08x\n", ( int )inlen, ( u32 )( v3 >> 32 ), ( u32 )v3 );
  printf( "(%3d) padding   %08x %08x\n", ( int )inlen, ( u32 )( b >> 32 ), ( u32 )b );
#endif
  v3 ^= b;
  SIPROUND;
  SIPROUND;
  v0 ^= b;
#ifdef xxxDEBUG
  printf( "(%3d) v0 %08x %08x\n", ( int )inlen, ( u32 )( v0 >> 32 ), ( u32 )v0 );
  printf( "(%3d) v1 %08x %08x\n", ( int )inlen, ( u32 )( v1 >> 32 ), ( u32 )v1 );
  printf( "(%3d) v2 %08x %08x\n", ( int )inlen, ( u32 )( v2 >> 32 ), ( u32 )v2 );
  printf( "(%3d) v3 %08x %08x\n", ( int )inlen, ( u32 )( v3 >> 32 ), ( u32 )v3 );
#endif
  v2 ^= 0xff;
  SIPROUND;
  SIPROUND;
  SIPROUND;
  SIPROUND;
  b = v0 ^ v1 ^ v2  ^ v3;
  U64TO8_LE( out, b );
  return 0;
}