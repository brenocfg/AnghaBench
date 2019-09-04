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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut32 ;
typedef  int const ut16 ;
struct optimised_sbox {int dummy; } ;

/* Variables and functions */
 int const BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BITSWAP8 (int const,int const,int const,int const,int const,int const,int const,int const,int const) ; 
 int /*<<< orphan*/  fn (int /*<<< orphan*/ ,struct optimised_sbox const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline ut16 feistel(ut16 val, const int *bitsA, const int *bitsB,
		const struct optimised_sbox* boxes1, const struct optimised_sbox* boxes2,
		const struct optimised_sbox* boxes3, const struct optimised_sbox* boxes4,
		ut32 key1, ut32 key2, ut32 key3, ut32 key4)
{
	ut8 l = BITSWAP8(val, bitsB[7],bitsB[6],bitsB[5],bitsB[4],bitsB[3],bitsB[2],bitsB[1],bitsB[0]);
	ut8 r = BITSWAP8(val, bitsA[7],bitsA[6],bitsA[5],bitsA[4],bitsA[3],bitsA[2],bitsA[1],bitsA[0]);

	l ^= fn(r, boxes1, key1);
	r ^= fn(l, boxes2, key2);
	l ^= fn(r, boxes3, key3);
	r ^= fn(l, boxes4, key4);

	return
		(BIT(l, 0) << bitsA[0]) |
		(BIT(l, 1) << bitsA[1]) |
		(BIT(l, 2) << bitsA[2]) |
		(BIT(l, 3) << bitsA[3]) |
		(BIT(l, 4) << bitsA[4]) |
		(BIT(l, 5) << bitsA[5]) |
		(BIT(l, 6) << bitsA[6]) |
		(BIT(l, 7) << bitsA[7]) |
		(BIT(r, 0) << bitsB[0]) |
		(BIT(r, 1) << bitsB[1]) |
		(BIT(r, 2) << bitsB[2]) |
		(BIT(r, 3) << bitsB[3]) |
		(BIT(r, 4) << bitsB[4]) |
		(BIT(r, 5) << bitsB[5]) |
		(BIT(r, 6) << bitsB[6]) |
		(BIT(r, 7) << bitsB[7]);
}