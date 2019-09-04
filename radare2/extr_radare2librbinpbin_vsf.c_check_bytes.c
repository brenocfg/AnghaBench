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

/* Variables and functions */
 int /*<<< orphan*/  VICE_MAGIC ; 
 scalar_t__ VICE_MAGIC_LEN ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool check_bytes(const ut8 *buf, ut64 length) {
	if (!buf || length < VICE_MAGIC_LEN) {
		return false;
	}
	return (!memcmp (buf, VICE_MAGIC, VICE_MAGIC_LEN));
}