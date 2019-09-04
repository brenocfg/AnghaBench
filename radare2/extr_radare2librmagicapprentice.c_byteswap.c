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
typedef  size_t ut32 ;
struct r_magic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bs1 (struct r_magic*) ; 

__attribute__((used)) static void byteswap(struct r_magic *magic, ut32 nmagic) {
	ut32 i;
	for (i = 0; i < nmagic; i++) {
		bs1 (&magic[i]);
	}
}