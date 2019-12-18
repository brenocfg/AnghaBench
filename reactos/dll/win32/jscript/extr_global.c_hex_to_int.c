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
typedef  int WCHAR ;

/* Variables and functions */
 scalar_t__ iswdigit (int const) ; 
 char towupper (int const) ; 

__attribute__((used)) static inline int hex_to_int(const WCHAR wch) {
    if(towupper(wch)>='A' && towupper(wch)<='F') return towupper(wch)-'A'+10;
    if(iswdigit(wch)) return wch-'0';
    return -1;
}