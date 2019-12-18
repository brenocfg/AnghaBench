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

/* Variables and functions */
 int /*<<< orphan*/  isascii (int /*<<< orphan*/ ) ; 
 scalar_t__ isdigit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hextoint(int c) {
	if (!isascii ((ut8)c)) {
		return -1;
	}
	if (isdigit ((ut8)c)) {
		return c - '0';
	}
	if ((c >= 'a') && (c <= 'f')) {
		return c + 10 - 'a';
	}
	if ((c >= 'A') && (c <= 'F')) {
		return c + 10 - 'A';
	}
	return -1;
}