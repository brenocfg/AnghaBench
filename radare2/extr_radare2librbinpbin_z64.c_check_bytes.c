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
typedef  scalar_t__ ut64 ;
typedef  scalar_t__ ut32 ;

/* Variables and functions */
 scalar_t__ N64_ROM_START ; 
 scalar_t__ r_read_be32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static bool check_bytes (const ut8 *buf, ut64 length) {
	ut32 magic = 0x80371240;
	if (length < N64_ROM_START) {
		return false;
	}
	return magic == r_read_be32 (buf);
}