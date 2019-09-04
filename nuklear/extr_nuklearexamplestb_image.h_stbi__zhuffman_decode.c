#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int* fast; } ;
typedef  TYPE_1__ stbi__zhuffman ;
struct TYPE_9__ {int num_bits; size_t code_buffer; } ;
typedef  TYPE_2__ stbi__zbuf ;

/* Variables and functions */
 size_t STBI__ZFAST_MASK ; 
 int /*<<< orphan*/  stbi__fill_bits (TYPE_2__*) ; 
 int stbi__zhuffman_decode_slowpath (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static int stbi__zhuffman_decode(stbi__zbuf *a, stbi__zhuffman *z)
{
   int b,s;
   if (a->num_bits < 16) stbi__fill_bits(a);
   b = z->fast[a->code_buffer & STBI__ZFAST_MASK];
   if (b) {
      s = b >> 9;
      a->code_buffer >>= s;
      a->num_bits -= s;
      return b & 511;
   }
   return stbi__zhuffman_decode_slowpath(a, z);
}