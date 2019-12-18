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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int MAXLEN ; 
 int /*<<< orphan*/  crypto_auth (scalar_t__*,scalar_t__*,int,scalar_t__*) ; 
 scalar_t__ memcmp (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/ * vectors ; 

__attribute__((used)) static int
test_vectors()
{
#define MAXLEN 64
  u8 in[MAXLEN], out[8], k[16];
  int i;
  int ok = 1;

  for( i = 0; i < 16; ++i ) k[i] = (u8)i;

  for( i = 0; i < MAXLEN; ++i )
  {
    in[i] = (u8)i;
    crypto_auth( out, in, i, k );

    if ( memcmp( out, vectors[i], 8 ) )
    {
      printf( "test vector failed for %d bytes\n", i );
      ok = 0;
    }
  }

  return ok;
}