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
typedef  unsigned int ut32 ;
typedef  scalar_t__ tableType_t ;

/* Variables and functions */
 int LZ4_HASHLOG ; 
 int MINMATCH ; 
 scalar_t__ const byut16 ; 

__attribute__((used)) static ut32 LZ4_hash4(ut32 sequence, tableType_t const tableType) {
	if (tableType == byut16) {
		return ((sequence * 2654435761U) >> ((MINMATCH*8)-(LZ4_HASHLOG+1)));
	}
	return ((sequence * 2654435761U) >> ((MINMATCH*8)-LZ4_HASHLOG));
}