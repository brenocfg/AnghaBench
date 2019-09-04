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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int* fe51 ;

/* Variables and functions */
 int MASK51 ; 
 int load_6 (int /*<<< orphan*/  const*) ; 
 int load_7 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void fe51_frombytes(fe51 h, const uint8_t *s)
{
    uint64_t h0 = load_7(s);                                /* 56 bits */
    uint64_t h1 = load_6(s + 7) << 5;                       /* 53 bits */
    uint64_t h2 = load_7(s + 13) << 2;                      /* 58 bits */
    uint64_t h3 = load_6(s + 20) << 7;                      /* 55 bits */
    uint64_t h4 = (load_6(s + 26) & 0x7fffffffffff) << 4;   /* 51 bits */

    h1 |= h0 >> 51; h0 &= MASK51;
    h2 |= h1 >> 51; h1 &= MASK51;
    h3 |= h2 >> 51; h2 &= MASK51;
    h4 |= h3 >> 51; h3 &= MASK51;

    h[0] = h0;
    h[1] = h1;
    h[2] = h2;
    h[3] = h3;
    h[4] = h4;
}