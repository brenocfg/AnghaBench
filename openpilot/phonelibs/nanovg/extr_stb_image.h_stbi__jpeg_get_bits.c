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
struct TYPE_4__ {int code_bits; unsigned int code_buffer; } ;
typedef  TYPE_1__ stbi__jpeg ;

/* Variables and functions */
 unsigned int* stbi__bmask ; 
 int /*<<< orphan*/  stbi__grow_buffer_unsafe (TYPE_1__*) ; 
 unsigned int stbi_lrot (unsigned int,int) ; 

__attribute__((used)) static int stbi__jpeg_get_bits(stbi__jpeg *j, int n)
{
   unsigned int k;
   if (j->code_bits < n) stbi__grow_buffer_unsafe(j);
   k = stbi_lrot(j->code_buffer, n);
   j->code_buffer = k & ~stbi__bmask[n];
   k &= stbi__bmask[n];
   j->code_bits -= n;
   return k;
}