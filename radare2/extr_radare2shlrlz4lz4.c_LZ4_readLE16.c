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
typedef  int ut8 ;
typedef  scalar_t__ ut16 ;

/* Variables and functions */
 scalar_t__ LZ4_isLittleEndian () ; 
 scalar_t__ LZ4_read16 (void const*) ; 

__attribute__((used)) static ut16 LZ4_readLE16(const void* memPtr) {
	if (LZ4_isLittleEndian()) {
		return LZ4_read16(memPtr);
	}
	const ut8* p = (const ut8*)memPtr;
	return (ut16)((ut16)p[0] + (p[1]<<8));
}