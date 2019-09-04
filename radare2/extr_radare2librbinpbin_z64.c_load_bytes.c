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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  int /*<<< orphan*/  RBinFile ;
typedef  int /*<<< orphan*/  N64Header ;

/* Variables and functions */
 scalar_t__ check_bytes (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 void* memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  n64_header ; 

__attribute__((used)) static bool load_bytes(RBinFile *bf, void **bin_obj, const ut8 *buf, ut64 sz, ut64 loadaddr, Sdb *sdb) {
	if (check_bytes (buf, sz)) {
		*bin_obj = memcpy (&n64_header, buf, sizeof (N64Header));
		return true;
	}
	return false;
}