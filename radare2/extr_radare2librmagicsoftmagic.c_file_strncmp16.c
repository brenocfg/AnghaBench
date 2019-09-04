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
typedef  int /*<<< orphan*/  ut64 ;
typedef  scalar_t__ ut32 ;

/* Variables and functions */
 int /*<<< orphan*/  file_strncmp (char const*,char const*,size_t,scalar_t__) ; 

__attribute__((used)) static ut64 file_strncmp16(const char *a, const char *b, size_t len, ut32 flags) {
	/*
	 * XXX - The 16-bit string compare probably needs to be done
	 * differently, especially if the flags are to be supported.
	 * At the moment, I am unsure.
	 */
	flags = 0;
	return file_strncmp(a, b, len, flags);
}