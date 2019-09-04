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
typedef  scalar_t__* longfelem ;
typedef  scalar_t__* felem ;

/* Variables and functions */
 int /*<<< orphan*/  felem_reduce_ (scalar_t__*,scalar_t__* const) ; 
 scalar_t__* zero100 ; 

__attribute__((used)) static void felem_reduce(felem out, const longfelem in)
{
    out[0] = zero100[0] + in[0];
    out[1] = zero100[1] + in[1];
    out[2] = zero100[2] + in[2];
    out[3] = zero100[3] + in[3];

    felem_reduce_(out, in);

    /*-
     * out[0] > 2^100 - 2^36 - 2^4 - 3*2^64 - 3*2^96 - 2^64 - 2^96 > 0
     * out[1] > 2^100 - 2^64 - 7*2^96 > 0
     * out[2] > 2^100 - 2^36 + 2^4 - 5*2^64 - 5*2^96 > 0
     * out[3] > 2^100 - 2^36 + 2^4 - 7*2^64 - 5*2^96 - 3*2^96 > 0
     *
     * out[0] < 2^100 + 2^64 + 7*2^64 + 5*2^96 < 2^101
     * out[1] < 2^100 + 3*2^64 + 5*2^64 + 3*2^97 < 2^101
     * out[2] < 2^100 + 5*2^64 + 2^64 + 3*2^65 + 2^97 < 2^101
     * out[3] < 2^100 + 7*2^64 + 7*2^96 + 3*2^64 < 2^101
     */
}