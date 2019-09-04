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
typedef  int uint64_t ;

/* Variables and functions */
 int bpf_rand_u16 (int) ; 
 int bpf_rand_u24 (int) ; 
 int bpf_rand_u32 (int) ; 
 int bpf_rand_u40 (int) ; 
 int bpf_rand_u48 (int) ; 
 int bpf_rand_u56 (int) ; 
 int bpf_rand_u64 (int) ; 
 int bpf_rand_u8 (int) ; 
 int rand () ; 

__attribute__((used)) static inline uint64_t bpf_semi_rand_get(void)
{
	switch (rand() % 39) {
	case  0: return 0x000000ff00000000ULL | bpf_rand_u8(0);
	case  1: return 0xffffffff00000000ULL | bpf_rand_u16(0);
	case  2: return 0x00000000ffff0000ULL | bpf_rand_u16(0);
	case  3: return 0x8000000000000000ULL | bpf_rand_u32(0);
	case  4: return 0x00000000f0000000ULL | bpf_rand_u32(0);
	case  5: return 0x0000000100000000ULL | bpf_rand_u24(0);
	case  6: return 0x800ff00000000000ULL | bpf_rand_u32(0);
	case  7: return 0x7fffffff00000000ULL | bpf_rand_u32(0);
	case  8: return 0xffffffffffffff00ULL ^ bpf_rand_u32(24);
	case  9: return 0xffffffffffffff00ULL | bpf_rand_u8(0);
	case 10: return 0x0000000010000000ULL | bpf_rand_u32(0);
	case 11: return 0xf000000000000000ULL | bpf_rand_u8(0);
	case 12: return 0x0000f00000000000ULL | bpf_rand_u8(8);
	case 13: return 0x000000000f000000ULL | bpf_rand_u8(16);
	case 14: return 0x0000000000000f00ULL | bpf_rand_u8(32);
	case 15: return 0x00fff00000000f00ULL | bpf_rand_u8(48);
	case 16: return 0x00007fffffffffffULL ^ bpf_rand_u32(1);
	case 17: return 0xffff800000000000ULL | bpf_rand_u8(4);
	case 18: return 0xffff800000000000ULL | bpf_rand_u8(20);
	case 19: return (0xffffffc000000000ULL + 0x80000ULL) | bpf_rand_u32(0);
	case 20: return (0xffffffc000000000ULL - 0x04000000ULL) | bpf_rand_u32(0);
	case 21: return 0x0000000000000000ULL | bpf_rand_u8(55) | bpf_rand_u32(20);
	case 22: return 0xffffffffffffffffULL ^ bpf_rand_u8(3) ^ bpf_rand_u32(40);
	case 23: return 0x0000000000000000ULL | bpf_rand_u8(bpf_rand_u8(0) % 64);
	case 24: return 0x0000000000000000ULL | bpf_rand_u16(bpf_rand_u8(0) % 64);
	case 25: return 0xffffffffffffffffULL ^ bpf_rand_u8(bpf_rand_u8(0) % 64);
	case 26: return 0xffffffffffffffffULL ^ bpf_rand_u40(bpf_rand_u8(0) % 64);
	case 27: return 0x0000800000000000ULL;
	case 28: return 0x8000000000000000ULL;
	case 29: return 0x0000000000000000ULL;
	case 30: return 0xffffffffffffffffULL;
	case 31: return bpf_rand_u16(bpf_rand_u8(0) % 64);
	case 32: return bpf_rand_u24(bpf_rand_u8(0) % 64);
	case 33: return bpf_rand_u32(bpf_rand_u8(0) % 64);
	case 34: return bpf_rand_u40(bpf_rand_u8(0) % 64);
	case 35: return bpf_rand_u48(bpf_rand_u8(0) % 64);
	case 36: return bpf_rand_u56(bpf_rand_u8(0) % 64);
	case 37: return bpf_rand_u64(bpf_rand_u8(0) % 64);
	default: return bpf_rand_u64(0);
	}
}