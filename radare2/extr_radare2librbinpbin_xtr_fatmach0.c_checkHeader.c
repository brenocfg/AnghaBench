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
typedef  int /*<<< orphan*/  const ut8 ;
typedef  int ut64 ;
typedef  int /*<<< orphan*/  ut32 ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  r_read_at_be32 (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static bool checkHeader(const ut8 *h, ut64 sz) {
	ut8 buf[4];
	if (sz >= 0x300 && !memcmp (h, "\xca\xfe\xba\xbe", 4)) {
		// XXX assuming BE
		ut64 off = (ut64)r_read_at_be32 (h, 4 * sizeof (ut32));
		if (off > 0 && off + 4 < sz) {
			memcpy (buf, h + off, 4);
			if (!memcmp (buf, "\xce\xfa\xed\xfe", 4) ||
				!memcmp (buf, "\xfe\xed\xfa\xce", 4) ||
				!memcmp (buf, "\xfe\xed\xfa\xcf", 4) ||
				!memcmp (buf, "\xcf\xfa\xed\xfe", 4)) {
				return true;
			}
		}
	}
	return false;
}