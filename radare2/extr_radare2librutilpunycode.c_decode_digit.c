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
typedef  int ut32 ;

/* Variables and functions */
 scalar_t__ IS_DIGIT (int) ; 
 int UT32_MAX ; 

__attribute__((used)) static ut32 decode_digit(ut32 v) {
	if (IS_DIGIT (v)) {
		return v - 22;
	}
	if (v >= 'a' && v <= 'z') {
		return v - 'a';
	}
	if (v >= 'A' && v <= 'Z') {
		return v - 'A';
	}
	return UT32_MAX;
}