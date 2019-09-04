#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  outlen; int /*<<< orphan*/ * h; } ;
typedef  TYPE_1__ blake2b_state ;
struct TYPE_7__ {int /*<<< orphan*/  digest_length; } ;
typedef  TYPE_2__ blake2b_param ;

/* Variables and functions */
 int /*<<< orphan*/  blake2b_init0 (TYPE_1__*) ; 
 int /*<<< orphan*/  load64 (int /*<<< orphan*/  const*) ; 

int blake2b_init_param( blake2b_state *S, const blake2b_param *P )
{
  const uint8_t *p = ( const uint8_t * )( P );
  size_t i;

  blake2b_init0( S );

  /* IV XOR ParamBlock */
  for( i = 0; i < 8; ++i )
    S->h[i] ^= load64( p + sizeof( S->h[i] ) * i );

  S->outlen = P->digest_length;
  return 0;
}