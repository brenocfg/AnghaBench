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
typedef  int ut64 ;
typedef  int ut16 ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,char*,int) ; 

__attribute__((used)) static bool knownHeader(const ut8 *buf,ut16 offset,ut64 length){
	// check for PE
	if (!memcmp (buf + offset, "PE", 2) &&
		(length > offset + 0x20) &&
		!memcmp (buf + offset + 0x18, "\x0b\x01", 2)) {
		return false;
	}
	// Check for New Executable, LE/LX or Phar Lap executable
	if (!memcmp (buf + offset, "NE", 2) ||
		!memcmp (buf + offset, "LE", 2) ||
		!memcmp (buf + offset, "LX", 2) ||
		!memcmp (buf + offset, "PL", 2)) {
		return false;
	}
	return true;
}