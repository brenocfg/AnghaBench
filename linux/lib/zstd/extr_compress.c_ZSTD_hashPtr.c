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
typedef  int U32 ;

/* Variables and functions */
 size_t ZSTD_hash4Ptr (void const*,int) ; 
 size_t ZSTD_hash5Ptr (void const*,int) ; 
 size_t ZSTD_hash6Ptr (void const*,int) ; 
 size_t ZSTD_hash7Ptr (void const*,int) ; 
 size_t ZSTD_hash8Ptr (void const*,int) ; 

__attribute__((used)) static size_t ZSTD_hashPtr(const void *p, U32 hBits, U32 mls)
{
	switch (mls) {
	// case 3: return ZSTD_hash3Ptr(p, hBits);
	default:
	case 4: return ZSTD_hash4Ptr(p, hBits);
	case 5: return ZSTD_hash5Ptr(p, hBits);
	case 6: return ZSTD_hash6Ptr(p, hBits);
	case 7: return ZSTD_hash7Ptr(p, hBits);
	case 8: return ZSTD_hash8Ptr(p, hBits);
	}
}