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
struct minidump_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDMP_MAGIC ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool check_bytes(const ut8 *buf, ut64 length) {
	return buf && (length > sizeof (struct minidump_header))
		&& (!memcmp (buf, MDMP_MAGIC, 6));
}